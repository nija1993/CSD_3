/* Definition of Renaming Register File */

#include "RRF.h"
#include <iostream>
#include <stdlib.h>
#include <iostream>

using namespace std;

RRF_Entry::RRF_Entry(){
	busy = false;
	valid = false;
}

RRF::RRF(int no){
	no_entries = no;
	rrf = new RRF_Entry[no_entries];
	no_occ = 0;
}

/* To add entry into rrf */
int RRF::add_entry(){
	int i = 0;
	for(; i < no_entries; i++) {
		if(rrf[i].valid == false) {
			rrf[i].busy = true;
			rrf[i].valid = true;
			break;
		}
	}
	if(i == no_entries-1)
		no_occ = no_entries;
	else
		no_occ = 0;
	return i+1;
}

void RRF::update(int index, uint64_t result){
	rrf[index-1].value = result;
	rrf[index-1].busy = false;
}

/* Returns false if there is no vacancy in rrf */
bool RRF::file_status(){
	if(no_occ == no_entries)
		return false;
	else
		return true;
}

void RRF::print(){
	cout << "-------------------------------------RRF-------------------------------------------------\n";
	cout << "index valid status value" << endl;
	for(int i = 0; i < no_entries; i++){
		cout << "| " << i << "\t" << rrf[i].valid << "\t" << rrf[i].busy << "\t" << rrf[i].value << "\t|" << endl;
	}
}







