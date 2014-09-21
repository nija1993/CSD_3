/* Declaration of Re-Order Buffer */

#ifndef ROB_H  
#define ROB_H

class ROB_Entry{
public :	
	int rrf_tag;
	bool exec_status, valid;
	void ROB_Entry(int rrf_t);
};

class ROB{
public :
	ROB_Entry* ROB;
	int no_entries, head, tail;
	ROB(int no);
};

#endif