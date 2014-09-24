#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include "ALU.h"
#include "ARF.h"
#include "RRF.h"
#include "ROB.h"

using namespace std;

int op_cycles[9];
ALU_unit *ALU1;
ALU_unit *ALU2;
ROB *reorder_buff;
Reserve_Stat *reserve_stat;
RRF *rrf;
ARF *arf;

/* Initializing the number of cycles taken for different operations */
void init_cycles(){
	op_cycles[0] = 2;
	op_cycles[1] = 2;
	op_cycles[2] = 3;
	op_cycles[3] = 3;
	op_cycles[4] = 1;
 	op_cycles[5] = 1;
	op_cycles[6] = 1;
	op_cycles[7] = 10;
	op_cycles[8] = 10;
}

/* Initializing the architechtural units */
void init_simulator(int a, int b, int c){
	ALU1 = new ALU_unit();
	ALU2 = new ALU_unit();
	reserve_stat = new Reserve_Stat(a);
	reorder_buff = new ROB(b);
	rrf = new RRF(c);
	arf = new ARF(8);
}

/* Reading instruction from an input file */
bool fetch_inst(){
	char line[100];
	line[0] = '\0';
	cin.getline(line, 95);
	if(line[0] == '\0')
		return false;
	else 
		return true;
}

/* Decoding the instruction, and placing in ARF and RRF */
void decode_inst(){

}

/* Executing the instruction */
void exec_inst(){
	
}

int main(){
	int a, b, c;
	bool fetched = false;
	int total_cycles = 0;
	cout << "Enter size of reservation station, reorder buffer and RRF respectively : " << endl;
	cin >> a >> b >> c;	
	init_cycles();
	init_simulator(a, b, c);
	while(1){
		exec_inst();
		if(fetched){
			decode_inst();
			fetched = false;
		}
		if(reserve_stat->array_status() && reorder_buff->queue_status()){
			fetched = fetch_inst();
		}
		total_cycles++;
		if(!reserve_stat->busy() && !reorder_buff->busy() && !fetched){
			break;
		}
	}
	cout << "no. of cycles : " << total_cycles << endl;
	return 0;
}





