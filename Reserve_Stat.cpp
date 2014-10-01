/* Definition of Reservation Station */

#include "Reserve_Stat.h"
#include <stdlib.h>
#include "global.h"
#include "RRF.h"
#include "ARF.h"
#include <iostream>

using namespace std;

extern ARF* arf;
extern RRF* rrf;

/* Constructor for resevation station entry */
Reserve_Entry::Reserve_Entry(){
	exec_status = EXEC_NOT_STARTED;
	inst_num = 0;
	op_code = 0;
	src1_tag = 0;
	src1_value = 0;
	src2_tag = 0;
	src2_value = 0;
	dest_tag = 0;
	dest_value = 0;
	valid = false;
}

/* Constructor for Reservation station */
Reserve_Stat::Reserve_Stat(int no){
	no_entries = no;
	first_unocc = 0;
	reserve_station = new Reserve_Entry[no];
}

/* To add entries to reservation station */
void Reserve_Stat::add_entry(Instruction* inst, int rrf_tag){
	reserve_station[first_unocc].valid = true;
	reserve_station[first_unocc].inst_num = inst->inst_num;
	reserve_station[first_unocc].op_code = inst->op_code;
	reserve_station[first_unocc].dest_tag = rrf_tag;
	if(inst->oper[1][0] == 'R'){
		int num = atoi((inst->oper[1])+1);
		if(!(arf->arf[num-1]).busy){
			reserve_station[first_unocc].src1_tag = 0;
			reserve_station[first_unocc].src1_value = arf->arf[num-1].value;
		}
		else{
			if(!(rrf->rrf[arf->arf[num-1].tag-1].busy)){
				reserve_station[first_unocc].src1_tag = 0;
				reserve_station[first_unocc].src1_value = rrf->rrf[arf->arf[num-1].tag-1].value;
			}
			else
				reserve_station[first_unocc].src1_tag = arf->arf[num-1].tag;
		}
	}
	else{
		reserve_station[first_unocc].src1_tag = 0;
		reserve_station[first_unocc].src1_value = atoi(inst->oper[1]);
	}
	if(inst->oper[2][0] != '\0'){
		if(inst->oper[2][0] == 'R'){
			int num = atoi((inst->oper[2])+1);
			if(!(arf->arf[num-1]).busy){
//				cout << "c1" << endl;
				reserve_station[first_unocc].src2_tag = 0;
				reserve_station[first_unocc].src2_value = arf->arf[num-1].value;
			}
			else{
				if(!(rrf->rrf[arf->arf[num-1].tag-1].busy)){
					reserve_station[first_unocc].src2_tag = 0;
					reserve_station[first_unocc].src2_value = rrf->rrf[arf->arf[num-1].tag-1].value;
//					cout << "c2" << endl;
				}
				else{
					reserve_station[first_unocc].src2_tag = arf->arf[num-1].tag;
//					cout << "c3" << endl;
				}
			}	
		}
		else{
			reserve_station[first_unocc].src2_tag = 0;
			reserve_station[first_unocc].src2_value = atoi(inst->oper[2]);
		}
	}
	reserve_station[first_unocc].exec_status = EXEC_NOT_STARTED;
	int e;
	for(e = first_unocc+1; e < no_entries; e++)
		if(reserve_station[e].valid == false){
			first_unocc = e;
			break;
		}
	if(e == no_entries)
		first_unocc = no_entries+1;
}

/* Returns true if reservation_station has vacancy to accomodate more entries*/
bool Reserve_Stat::array_status(){
	if(first_unocc == no_entries+1)
		return false;
	else
		return true;
}

/* Poll rrf table to find out if the a particular instruction is ready for execution */
//bool Reserve_Stat::poll_rrf(int reg_no){
//	return false;	
//}

void Reserve_Stat::update(int rrfTag, int result){
	for(int i = 0; i < no_entries; i++){
		if(reserve_station[i].dest_tag == rrfTag){
			reserve_station[i].valid = false;
			if(i < first_unocc)
				first_unocc = i;
		}
		if(reserve_station[i].valid == true){
			if(reserve_station[i].src1_tag == rrfTag){
				reserve_station[i].src1_tag = 0;
				reserve_station[i].src1_value = result;
			}
			if(reserve_station[i].src2_tag == rrfTag){
				reserve_station[i].src2_tag = 0;
				reserve_station[i].src2_value = result;
			}
		}
	}
}

/* Returns if the reservation station is busy or free */
bool Reserve_Stat::busy(){
	for(int i = 0; i < no_entries; i++)
		if(reserve_station[i].valid)
			return true;
	return false;
}

void Reserve_Stat::print() {
	cout << "--------------------------Reserve_Station------------------------------------\n";
	cout << "index valid opcode dest, src1, value1, src2, value2, status" << endl;
	for(int i = 0; i < no_entries; i++) {
		cout << i << "\t" << reserve_station[i].valid << "\t" << reserve_station[i].op_code << "\t" << reserve_station[i].dest_tag << "\t" << reserve_station[i].src1_tag << "\t" << reserve_station[i].src1_value << "\t" << reserve_station[i].src2_tag << "\t" << reserve_station[i].src2_value << "\t" << reserve_station[i].exec_status << "\t" << endl;
	}
}

void Reserve_Stat::set_first_unocc(int no){
	if(no < first_unocc)
		first_unocc = no;
}




