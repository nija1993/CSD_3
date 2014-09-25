/* Definition of Renaming Register File */

#include "RRF.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

RRF_Entry::RRF_Entry(int arf_e){
	arf_entry = arf_e;
	busy = false;
	valid = false;
}

void RRF_Entry::commit(uint64_t value){
	this->value = value;
}

RRF::RRF(int no){
	no_entries = no;
	rrf = (RRF_Entry*)malloc(no*sizeof(RRF_Entry));
	for(int i = 0; i < no; i++) {
		rrf[i] = RRF_Entry(0);
	}
	no_occ = 0;
}

/* To add entry into rrf */
int RRF::add_entry(int arf_off){
	int i = 0;
	for(; i < no_entries; i++) {
		if(rrf[i].valid == false) {
			arf_entry = arf_off;
			busy = true;
			valid = true;
			break;
		}
	}
	return i+1;
}

/* Returns false if there is no vacancy in rrf */
bool RRF::file_status(){
	if(no_occ == no_entries)
		return false;
	else
		return true;
}




