/* Declaration of Re-Order Buffer */

#ifndef ROB_H  
#define ROB_H

class ROB_Entry{
public :	
	int rrf_tag;
	bool exec_status, valid;
	ROB_Entry(int rrf_t);
};

class ROB{
public :
	ROB_Entry* rob;
	int no_entries, head, tail;
	ROB(int no);					// constructor 
	void add_entry(ROB_Entry );		// to add entries into ROB queue
	bool queue_status();			// returns the status of queue if it has vacancy
	bool busy();					// returns if ROB is busy or not
};

#endif
