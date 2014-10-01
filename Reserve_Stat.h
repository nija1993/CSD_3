/* Declaration of Reservation Station */

#ifndef RESERVE_STAT_H  
#define RESERVE_STAT_H
#include <stdint.h>
#include "inst.h"

class Reserve_Entry {
public :
	int op_code;
	int inst_num;
	bool valid;
	int src1_tag, src2_tag, dest_tag;
	uint64_t src1_value, src2_value, dest_value;
	int exec_status;
	Reserve_Entry();
};

class Reserve_Stat {
	int first_unocc;
	int no_entries;
public : 
	Reserve_Entry* reserve_station;
	void update(int rrfTag, int result);		 // Update the sources of instructions which have rrfTag as tag with result 
	Reserve_Stat(int no);		// constructor
	void add_entry(Instruction* , int);		// To add entry to reservation station
	bool array_status();		// returns if the resevation status has vacancy or not
	bool busy();				// returns if the resevation station is busy
	void print();
	void set_first_unocc(int no);
};


#endif



