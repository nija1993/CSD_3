/* Definition of Architechture Register File */

#include "ARF.h"
#include <iostream>

using namespace std;

void ARF_Entry::ARF_Entry(int offs, int tag){
	offset = offs;
	tag = t;
	busy = false;
	value = 0;
}

void ARF_Entry::commit(uint64_t value){
	this.value = value;
}

void ARF::ARF(int no){
	no_entries = no;
	arf = (ARF_Entry*)malloc(no * sizeof(ARF_Entry));
}


