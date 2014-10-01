#include "ALU.h"
#include <stdlib.h>
#include "global.h"

ALU_unit::ALU_unit(int* op_c) {
	op_cycles = op_c;
	result = 0;
}

void ALU_unit::load_operands(int op, int op1, int op2){
	this->op = op;
	this->op1 = op1;
	this->op2 = op2;
}

void ALU_unit::execute() {
	cycles = op_cycles[op-1];
	switch(op) {
		case ADD:
			result = op1 + op2;
			break;
		case SUB:
			result = op1 - op2;
			break;
		case MUL:
			result = op1 * op2;
			break;
		case DIV:
			result = op1 / op2;
			break;
		case AND:
			result = op1 & op2;
			break;
		case OR:
			result = op1 | op2;
			break;
		case XOR:
			result = op1 ^ op2;
			break;
	}
}

/* Sets number of cycles required for execution */
void ALU_unit::set_no_cycles(int no){
	cycles = no;
}

/* returns 0 if num_cycles left is 0, otherwise -1 */
int ALU_unit::cycles_left(){
	if(cycles == 0)
		return -1;
	cycles--;
	if(cycles == 0)
		return 0;
	else 
		return 1;
}

/* Obtain result from ALU unit */
int ALU_unit::get_result(){
	return result;
}





