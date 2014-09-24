/* Definition of Architechture Register File */

#include "ROB.h"
#include <iostream>
#include <malloc.h>

using namespace std;

ROB_Entry::ROB_Entry(int rrf_t){
	rrf_tag = rrf_t;
	exec_status = false;
	valid = false;
}

ROB::ROB(int no){
	no_entries = no;
	head = no_entries-1;
	tail = no_entries-1;
	rob = (ROB_Entry*)malloc(no * sizeof(ROB_Entry));
}

void ROB::add_entry(ROB_Entry entry){
	rob[head] = entry;
	head--;
	if(head < 0)
		head = no_entries-1;
}

bool ROB::queue_status(){
	if(head == (tail+1)%no_entries)
		return false;
	else
		return true;
}

bool ROB::busy(){
	if(tail == head)
		return false;
	else
		return true;
}





