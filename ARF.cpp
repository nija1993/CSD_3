/* Definition of Architechture Register File */

#include "ARF.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

ARF_Entry::ARF_Entry(){
	tag = 0;
	busy = false;
	value = 0;
}

void ARF_Entry::commit(uint64_t value){
	this->value = value;
}

ARF::ARF(int no){
	no_entries = no;
	arf = new ARF_Entry[no];
}

void ARF::print(){
	cout << "---------------------------ARF-----------------------------------\n";
	cout << "index status tag value" << endl;
	for(int i = 0; i < no_entries; i++){
		cout << "| " << i << "\t" << arf[i].busy << "\t" << arf[i].tag << "\t" << arf[i].value << "\t|" << endl;
	}
}

void ARF::init_regs(int* input){
	for(int i = 0; i < no_entries; i++){
		arf[i].value = input[i];
	}
}







