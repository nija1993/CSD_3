/* Definition of Architechture Register File */

#include "RRF.h"
#include <iostream>

using namespace std;

void ARF_Entry::ARF_Entry(int offs, int tag){
	offset = offs;
	tag = t;
	busy = false;
	value = 0;
}

void 

void ARF::ARF(int no){
	no_entries = no;
	arf = (ARF_Entry*)malloc(no * sizeof(ARF_Entry));
}


