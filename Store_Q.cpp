#include "Store_Q.h"
#include <limits.h>
#include <iostream>

using namespace std;

Store_Q_Entry::Store_Q_Entry() {
	inst_num = 0;
	address = -1;
	value = 0;
	valid = false;
	completed = false;
	to_set_complete = false;
}

Store_Q::Store_Q(int no) {
	no_entries = no;
	store = new Store_Q_Entry[no_entries];
}

void Store_Q::add_entry(int inst, int addr, int val) {
	for(int i = 0; i < no_entries; i++) {
		if(!store[i].valid){
			store[i].valid = true;
			store[i].inst_num = inst;
			store[i].address = addr;
			store[i].value = val;
			break;
		}
	}
}

bool Store_Q::probe(int addr, int inst) {
	for(int i = 0; i < no_entries; i++) {
		if(store[i].valid && store[i].address == addr && store[i].inst_num < inst)
			return true;
	}
	return false;
}

int Store_Q::search(int addr, int inst) {
	int rec_inst_addr = 0;
	int val = -1;
	for(int i = 0; i < no_entries; i++) {
		if(store[i].valid && store[i].address == addr && store[i].inst_num < inst && store[i].inst_num > rec_inst_addr) {
			rec_inst_addr = store[i].inst_num;
			val = store[i].value;
		}
	}
	return val;
}

/* Returns true if there is vacancy in store queue */
bool Store_Q::check_vacancy(){
	for(int i = 0; i < no_entries; i++)
		if(store[i].valid == false)
			return true;
	return false;
}

/* Remove the least numbered instruction from store queue */
int Store_Q::remove_least_completed() {
	int min = INT_MAX;
	int index = -1;
	for(int i = 0; i < no_entries; i++) {
		if(store[i].valid && store[i].inst_num < min){
			min = store[i].inst_num;
			index = i;
		}
	}
	if(index != -1 && store[index].completed)
		return index;
	return -1;
}

/* Returns true if store queue is busy */
bool Store_Q::busy(){
	for(int i = 0; i < no_entries; i++){
		if(store[i].valid)
			return true;
	}
	return false;
}

void Store_Q::print() {
	cout << "-----------------Store Q-----------------\n";
	cout << "valid inst completed address value" << endl;
	for(int i = 0; i < no_entries; i++) {
		cout << store[i].valid << "\t" << store[i].inst_num << "\t" << store[i].completed << "\t" << store[i].address << "\t" << store[i].value << endl;
	}
}

void Store_Q::set_complete(){
	for(int i = 0; i < no_entries; i++){
		if(store[i].valid && store[i].to_set_complete){
			store[i].completed = true;
			store[i].to_set_complete = false;
		}
	}
}






