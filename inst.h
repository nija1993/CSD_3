#ifndef INST_H
#define INST_H

class Instruction {
public:
	int inst_num;
	int op_code;
	char oper[3][15];
	Instruction(char* line, int num);
};

#endif
