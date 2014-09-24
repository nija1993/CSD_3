
#ifndef ALU_H
#define ALU_H

#include "Reserve_Stat.h"

class ALU_unit {
	int op;
	int cycles;
	int op1, op2, result;
public:
	ALU_unit();					// constructor
	void load_operands(int, int, int);		// load operands into ALU unit
	void execute();				// to execute instruction
	int get_result();			// get the result after execution
	void set_no_cycles(int );	// set number of cycles taken for the instruction
	int cycles_left();			// number of cycles left to	complete execution of assigned task 
};

#endif
