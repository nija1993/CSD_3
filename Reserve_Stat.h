/* Declaration of Reservation Station */

#ifndef RESERVE_STAT_H  
#define RESERVE_STAT_H

#define ADD 1
#define SUB 2
#define MUL 3
#define DIV 4
#define AND 5
#define OR 6
#define XOR 7
#define LOAD 8
#define STORE 9

#define EXEC_NOT_STARTED -1
#define EXEC_STARTED 0
#define EXEC_DONE 1

class Reserve_Entry {
public :
	int op_code;
	int src1_tag, src2_tag, dest_tag;
	uint64_t src1_value, src2_value, dest_value;
	int exec_start;
	Reserve_Entry();
};

class Reserve_Stat {
	Reserve_Entry* reserve_station;
	int no_entries;
public : 
	Reserve_Stat(int no);
};

#endif