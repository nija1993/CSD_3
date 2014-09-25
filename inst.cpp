/* Definition of instruction */

#include "inst.h"
#include "global.h"
#include <iostream>

using namespace std;

extern int op_cycles[9];

Instruction::Instruction(char* line, int num){
	inst_num = num;
	int i = 0, k = 0;
	switch(line[0]){
		case 'A':
			if(line[1] == 'D')
				op_code = ADD;
			else
				op_code = AND;
			i = 3;
			break;
		case 'S':
			if(line[1] == 'U'){
				op_code = SUB;
				i = 3;
			}
			else{
				op_code = STORE;
				i = 5;
			}
			break;
		case 'M':
			op_code = MUL;
			i = 3;
			break;
		case 'D':
			op_code = DIV;
			i = 3;
			break;
		case 'O':
			op_code = OR;
			i = 2;
			break;
		case 'X':
			op_code = XOR;
			i = 3;
			break;
		case 'L':
			op_code = LOAD;
			i = 4;
			break;
	}
	int x = 0;
	while(line[i] != '\0'){
		k = 0;
		i++;
		while(line[i] != ' ' && line[i] != '\0'){
			oper[x][k] = line[i];
			i++;
			k++;
		}
		x++;
	}
}







