/* Definition of Architechture Register File */

#include "ROB.h"
#include <iostream>

using namespace std;

void ROB_Entry::ROB_Entry(int rrf_t){
	rrf_tag = rrf_t;
	exec_status = false;
	valid = false;
}

void ROB::ROB(int no){
	no_entries = no;
	ROB = (ROB_Entry*)malloc(no * sizeof(ROB_Entry));
}


