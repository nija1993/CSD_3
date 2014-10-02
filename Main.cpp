#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include "ALU.h"
#include "ARF.h"
#include "RRF.h"
#include "ROB.h"
#include "inst.h"
#include "global.h"
#include "Store_Q.h"
#include "Reserve_Stat.h"

using namespace std;

ALU_unit* ALU[2];
Reserve_Stat* reserve_stat;
ROB* reorder_buff;
RRF* rrf;
ARF* arf;
Store_Q* store_q;

int no_rrf = 0;
int no_arf = 8;
int no_reserve = 0;
int no_rob = 0;
int no_store = 0;
int memory[101];

char curr_inst[100];

int* op_cycles;

void init_memory() {
	for(int i = 0; i <= 100; i++)
		memory[i] = i;
}

/* Initializing the number of cycles taken for different operations */
void init_cycles(){
	op_cycles = new int[9];
	op_cycles[0] = 2;
	op_cycles[1] = 2;
	op_cycles[2] = 3;
	op_cycles[3] = 3;
	op_cycles[4] = 1;
 	op_cycles[5] = 1;
	op_cycles[6] = 1;
	op_cycles[7] = 10;
	op_cycles[8] = 10;
}

/* Initializing the architechtural units */
void init_simulator(int a, int b, int c, int d){
	ALU[0] = new ALU_unit(op_cycles);
	ALU[1] = new ALU_unit(op_cycles);
	reserve_stat = new Reserve_Stat(a);
	reorder_buff = new ROB(b);
	rrf = new RRF(c);
	arf = new ARF(8);
	store_q = new Store_Q(d);
}

/* Reading instruction from an input file */
bool fetch_inst(){
	gets(curr_inst);
	cout << curr_inst << endl;
	if(curr_inst[0] == '\0')
		return false;
	else 
		return true;
}

/* Decoding the instruction, and placing in ARF and RRF */
void decode_inst(int inst_num){
	Instruction* inst = new Instruction(curr_inst, inst_num);
	int result_tag;
	int temp_tag;
	if(inst->op_code != STORE)
	{
		result_tag = atoi((inst->oper[0])+1)-1;
		temp_tag = rrf->add_entry();
		reserve_stat->add_entry(inst, temp_tag);
		arf->arf[result_tag].tag = temp_tag;
		arf->arf[result_tag].busy = true;
		reorder_buff->add_entry(temp_tag, inst_num);
	}
	else{
		reserve_stat->add_entry(inst, 0);
//	cout << "temp_tag : " << temp_tag << endl;
		reorder_buff->add_entry(0, inst_num);
	}
}

/* Executing the instruction */
int exec_inst(int k){
	bool flag = false;
	Reserve_Entry entry;
	for(int i = 0; i < no_reserve; i++){
		if(reserve_stat->reserve_station[i].valid && reserve_stat->reserve_station[i].exec_status == EXEC_NOT_STARTED){
			entry = reserve_stat->reserve_station[i];
			if((entry.src1_tag == 0 || !rrf->rrf[entry.src1_tag-1].busy) && (entry.src2_tag == 0 || !rrf->rrf[entry.src2_tag-1].busy)){
				if(entry.src1_tag != 0)
					reserve_stat->reserve_station[i].src1_value = rrf->rrf[entry.src1_tag-1].value;
				if(entry.src2_tag != 0)
					reserve_stat->reserve_station[i].src2_value = rrf->rrf[entry.src2_tag-1].value;
				if(entry.op_code != STORE && entry.op_code != LOAD){
					ALU[k]->load_operands(entry.op_code, reserve_stat->reserve_station[i].src1_value, reserve_stat->reserve_station[i].src2_value);
					ALU[k]->execute();
					ALU[k]->cycles_left();
					flag = true;
					reserve_stat->reserve_station[i].exec_status = EXEC_STARTED;
					break;	
				}
			}
		}
	}
	if(flag)
		return entry.dest_tag;
	else
		return -1;
}

/* Commit instruction */
void commit_inst(){
	int head = reorder_buff->head;
	int tail = reorder_buff->tail;
	if(head < tail)
		head = head + no_rob;
	for(int j = head; j >= tail; j--){
		ROB_Entry entry = reorder_buff->rob[j % no_rob];
		if(tail != no_rob && !entry.exec_status){
			reorder_buff->rob[j % no_rob].valid = false;
			if(entry.rrf_tag == 0){
				for(int k = 0; k < no_store; k++) {
					if(store_q->store[k].valid && entry.inst_num == store_q->store[k].inst_num)
						store_q->store[k].completed = true;
				}
			}
			else{
				for(int i = 0; i < arf->no_entries; i++){
					if(arf->arf[i].tag == entry.rrf_tag){
						arf->arf[i].value = rrf->rrf[entry.rrf_tag-1].value;
						rrf->rrf[entry.rrf_tag-1].valid = false;
						arf->arf[i].busy = false;			
					}
				}
			}
			if(head == tail){
				reorder_buff->head = no_rob - 1;
				reorder_buff->tail = no_rob;
				break;
			}
			if(reorder_buff->head != 0)
				reorder_buff->head--;
			else
				reorder_buff->head += no_rob - 1;
		}
		else 
			break;
	}
}

/* Initialize the ARF registers */
void initialize_regs(){
	for(int i = 0; i < no_arf; i++)
		arf->arf[i].value = 0;
}

int check_load_inRS(){
	int ret = -1;
	for(int i = 0; i < no_reserve; i++){
		Reserve_Entry entry = reserve_stat->reserve_station[i];
		if(entry.op_code == LOAD && entry.valid && entry.src1_tag == 0){
			ret = i;
			int addr = entry.src1_value;
			if(store_q->probe(addr, entry.inst_num))
				return i;
		}
	}
	return ret;
}

int check_store_inRS() {
	bool flag;
	for(int i = 0; i < no_reserve; i++){
		flag = false;
		Reserve_Entry entry = reserve_stat->reserve_station[i];
		if(entry.op_code == STORE && entry.valid && entry.src1_tag == 0 && entry.src2_tag == 0){
			for(int j = 0; j < no_reserve; j++){
				Reserve_Entry en = reserve_stat->reserve_station[j];
				if(en.op_code == STORE && !entry.valid && (entry.inst_num > en.inst_num) && (en.src1_tag != 0  || en.src2_tag != 0  || en.src1_value == entry.src1_value)) {
					flag = true;
					break;
				}
			}
			if(flag == false)
				return i;
		}
	}
	return -1;
}

/* Main Program */
int main(int argc, char** argv){
	bool fetched = false;
	int total_cycles = 0;
	int inst_num = 0;
	cout << "Enter size of reservation station, reorder buffer and RRF respectively : " << endl;
	init_cycles();
	init_memory();
	no_reserve = atoi(argv[1]);
	no_rob = atoi(argv[2]);
	no_rrf = atoi(argv[3]);
	no_store = atoi(argv[4]);
	init_simulator(no_reserve, no_rob, no_rrf, no_store);
	initialize_regs();
	int s1 = 0, s2 = 0;
	int rrf_reg1, rrf_reg2;
	int index_load;
	int load_unit_cycles = -1;
	int store_unit_cycles = -1;
	int index_store = -1;
	int value = 0;
	Store_Q_Entry s_entry;
	bool memory_accessed = false;
	bool value_valid = false;
	uint64_t result;
	while(1){
		// cout << "cycles " << total_cycles << endl;
		
		// Commit ROB
		commit_inst();
		
		//Read into ALU unit if free
		s1 = ALU[0]->cycles_left();
		if(s1 == -1){
			rrf_reg1 = exec_inst(0);
			if(rrf_reg1 != -1)
				s1 = ALU[0]->cycles;
		}
		s2 = ALU[1]->cycles_left();
		if(s2 == -1){
			rrf_reg2 = exec_inst(1);
			if(rrf_reg2 != -1)
				s2 = ALU[1]->cycles;
		}
		
		//Load unit takes over, only to check if store queue has value for load instruction ready to be executed
		if(load_unit_cycles == -1){
			index_load = check_load_inRS();
			//cout << "check load : " << index_load << endl;
			if(index_load != -1){
				//load_unit_cycles = op_cycles[LOAD-1];
				Reserve_Entry entry = reserve_stat->reserve_station[index_load]; 
				if(store_q->probe(entry.src1_value, entry.inst_num))
				{
					cout << "probe success" << endl;
					value = store_q->search(entry.src1_value, entry.inst_num);
					value_valid = true;
					load_unit_cycles = 0;
				}
			}
		}	
		/* In store queue, all the store instructions which are ready to be committed are filled in queue. If 
				store queue becomes full, then store gets more priority over load */
		while(store_q->check_vacancy()){
			index_store = check_store_inRS();
		//	cout << "calling this" << endl;
			if(index_store == -1)
				break;
			Reserve_Entry entry = reserve_stat->reserve_station[index_store];
			store_q->add_entry(entry.inst_num, entry.src1_value, entry.src2_value);
			reserve_stat->reserve_station[index_store].valid = false;
			reserve_stat->set_first_unocc(index_store);
			reorder_buff->set_exec_inst_done(entry.inst_num);
		}
		
		/* All store instructions ready to be committed are in the queue */
		bool schedule_store = false;
		if(index_store == -1 && memory_accessed == false){
			if(load_unit_cycles == -1){
				if(index_load != -1){
					// schedule load instruction
					if(!memory_accessed){
						load_unit_cycles = op_cycles[LOAD-1];
						memory_accessed = true;
					}
				}
				else
					schedule_store = true;
			}
		}
		/* The queue is full before all store instructions ready to be executed are not put */
		// scheduling store instruction
		if((index_store != -1 || schedule_store) && memory_accessed == false){
//			cout << "entering store memory.. \n";
			int abc = store_q->remove_least_completed();
//			cout << "abc : " << abc << endl;
			if(abc != -1) {
				s_entry = store_q->store[abc];
				memory_accessed = true;
//				cout << "opcycles : " << op_cycles[STORE-1] << ;
				store_unit_cycles = op_cycles[STORE-1];
				store_q->store[abc].valid = false;
			}
				
		}
		
		//ALU commit
		if(s1 == 0){
			result = ALU[0]->get_result();
			rrf->update(rrf_reg1, result);
			reserve_stat->update(rrf_reg1, result);
			reorder_buff->set_exec_done(rrf_reg1);
		}
		
		if(s2 == 0){
			result = ALU[1]->get_result();
			rrf->update(rrf_reg2, result);
			reserve_stat->update(rrf_reg2, result);
			reorder_buff->set_exec_done(rrf_reg2);
		}
		
		
		if(load_unit_cycles != -1){
			load_unit_cycles--;
		}
		if(store_unit_cycles != -1){
			store_unit_cycles--;
		}
		
		//Load commit
		if(load_unit_cycles == 0) {
			Reserve_Entry entry = reserve_stat->reserve_station[index_load];
			cout << "value valid : " << value_valid << "address : " << entry.src1_value << endl;
			if(value_valid){
				value_valid = false;
			}
			else{
				value = memory[entry.src1_value];
			}
			rrf->update(entry.dest_tag, value);
			reserve_stat->update(entry.dest_tag, value);
			reorder_buff->set_exec_done(entry.dest_tag);
			load_unit_cycles = -1;
			memory_accessed = false;
		}
		//Store commit
		if(store_unit_cycles == 0) {
			memory_accessed = false;
			memory[s_entry.address] = s_entry.value;
			store_unit_cycles = -1;
		}
		//cout << "memory accessed " << memory_accessed << " store_unit_cycles " << store_unit_cycles << endl;
		
		//Decode instruction 
		if(fetched){
			inst_num++;
			decode_inst(inst_num);
			cout << "decoded " << endl;
			fetched = false;
		}
		//reserve_stat->print();
		//rrf->print();
		//arf->print();
		reorder_buff->print();
		store_q->print();
		cout << "=============================================================" << endl;
		//Fetch instruction
		if(reserve_stat->array_status() && reorder_buff->queue_status() && rrf->file_status()){
			fetched = fetch_inst();
		}
		total_cycles++;
		cout << "end of cycle no : " << total_cycles << endl;
		//cout << reserve_stat->busy() << reorder_buff->busy() << fetched << store_q->busy() << memory_accessed << endl;
		if(!reserve_stat->busy() && !reorder_buff->busy() && !fetched && !store_q->busy() && !memory_accessed){
			break;
		}
//		if(total_cycles == 100)
//			break;
	}
	cout << "no. of cycles : " << total_cycles << endl;
	return 0;
}



