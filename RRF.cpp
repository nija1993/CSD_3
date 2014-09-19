/* Definition of Renaming Register File */

#include "RRF.h"
#include <iostream>

using namespace std;

RRF_Entry::RRF_Entry(int offs, int arf_e){
	offset = offs;
	arf_entry = arf_e;
	busy = false;
	valid = false;
}

void RRF_Entry::commit(uint64_t value){
	this.value = value;
}

RRF::RRF(int no){
	no_entries = no;
	rrf = (RRF_Entry*)malloc(no * sizeof(RRF_Entry));
}

