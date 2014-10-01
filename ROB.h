/* Declaration of Re-Order Buffer */

#ifndef ROB_H  
#define ROB_H
#include <stdint.h>
#include "inst.h"

class ROB_Entry{
public :	
	int rrf_tag;
	bool exec_status, valid;		// exec_status is false if execution is done
	int inst_num;
	ROB_Entry(int, int);
};

class ROB{
public :
	ROB_Entry* rob;
	int no_entries, head, tail;
	ROB(int no);					// constructor 
	void add_entry(int, int);		// to add entries into ROB queue
	bool queue_status();			// returns the status of queue if it has vacancy
	bool busy();					// returns if ROB is busy or not
	void set_exec_done(int );		// sets the execution status of entry to "false"
	void set_exec_inst_done(int);	// sets the execution status of entry corresponding to the instruction to "false"
	void print(); 
};

#endif
