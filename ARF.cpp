/* Definition of Architechture Register File */

#include "ARF.h"
#include <stdlib.h>

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


