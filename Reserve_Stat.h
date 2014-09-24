/* Declaration of Reservation Station */

#ifndef RESERVE_STAT_H  
#define RESERVE_STAT_H
#include <stdint.h>
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
	int first_unocc;
	Reserve_Entry* reserve_station;
	int no_entries;
public : 
	Reserve_Stat(int no);		// constructor
	void add_entry(Reserve_Entry );		// To add entry to reservation station
	bool array_status();		// returns if the resevation status has vacancy or not
	bool poll_rrf(int );			// polls rrf to
	bool busy();				// returns if the resevation station is busy
};


#endif



