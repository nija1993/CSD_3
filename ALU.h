
#ifndef ALU_H
#define ALU_H

class ALU_unit {
	int op;
	int op1, op2, result;
	int* op_cycles;
public:
	int cycles;
	ALU_unit(int*);					// constructor
	void load_operands(int, int, int);		// load operands into ALU unit
	void execute();				// to execute instruction
	int get_result();			// get the result after execution
	void set_no_cycles(int );	// set number of cycles taken for the instruction
	int cycles_left();			// number of cycles left to	complete execution of assigned task 
};

#endif
