
#include "ALU.h"

ALU_unit::ALU_unit(int op, int op1, int op2) {
	this.op = op;
	this.op1 = op1;
	this.op2 = op2;
	result = 0;
}

void ALU_unit::execute() {
	switch(op) {
		case 1:
			result = op1 + op2;
			break;
		case 2:
			result = op1 - op2;
			break;
		case 3:
			result = op1 * op2;
			break;
		case 4:
			result = op1 / op2;
			break;
		case 5:
			result = op1 & op2;
			break;
		case 6:
			result = op1 | op2;
			break;
		case 7:
			result = op1 ^ op2;
			break;
	}
}
