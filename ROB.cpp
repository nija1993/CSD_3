/* Definition of Architechture Register File */

#include "ROB.h"
#include <iostream>

using namespace std;

ROB_Entry::ROB_Entry(int rrf_t){
	rrf_tag = rrf_t;
	exec_status = false;
	valid = false;
}

ROB::ROB(int no){
	no_entries = no;
	head = 0;
	tail = 0;
	rob = (ROB_Entry*)malloc(no * sizeof(ROB_Entry));
}


