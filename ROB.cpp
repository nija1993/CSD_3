/* Definition of Architechture Register File */

#include "ROB.h"
#include <iostream>
#include <malloc.h>
#include <iostream>

using namespace std;

ROB_Entry::ROB_Entry(int rrf_t, int inst_n){
	rrf_tag = rrf_t;
	inst_num = inst_n;
	exec_status = false;
	valid = false;
}

ROB::ROB(int no){
	no_entries = no;
	head = no_entries-1;
	tail = no_entries;
	rob = (ROB_Entry*)malloc(no * sizeof(ROB_Entry));
}

void ROB::add_entry(int rrf_t, int inst_n){
	tail--;
	if(tail < 0)
		tail = no_entries-1;
	rob[tail] = ROB_Entry(rrf_t, inst_n);
	rob[tail].valid = true;
	rob[tail].exec_status = true;
}

/* Returns true if the queue has vacancy */
bool ROB::queue_status(){
	if(head == (tail-1) % no_entries && tail != no_entries)
		return false;
	else
		return true;
}

bool ROB::busy(){
	if(tail == no_entries)
		return false;
	else
		return true;
}

void ROB::set_exec_done(int rrfTag){
	if(head < tail)
		head = head + no_entries;
	for(int i = head; i >= tail && tail != no_entries; i--){
		if(rob[i % no_entries].rrf_tag == rrfTag)
			rob[i % no_entries].exec_status = false;
	}
	head = head % no_entries;
}

void ROB::set_exec_inst_done(int inst) {
	if(head < tail)
		head = head + no_entries;
	for(int i = head; i >= tail && tail != no_entries; i--){
		if(rob[i % no_entries].inst_num == inst)
			rob[i % no_entries].exec_status = false;
	}
	head = head % no_entries;
}

void ROB::print(){
	cout << "-------------------------ROB---------------------------------\n";
	if(head < tail)
		head = head + no_entries;
	cout << "inst_num exec_status rrf_tag" << endl;
	for(int i = head; i >= tail && tail != no_entries; i--){
		cout << rob[i % no_entries].inst_num << "\t" << rob[i % no_entries].exec_status << "\t" << rob[i % no_entries].rrf_tag << endl;
	}
	head = head % no_entries;
	
}






