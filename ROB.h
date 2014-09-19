/* Declaration of Re-Order Buffer */

#ifndef ROB_H  
#define ROB_H

class ROB_Entry{
	int rrf_tag;
	bool exec_status, valid;
public :	
	void ROB_Entry(int rrf_t);
}

class ROB{
	ROB_Entry* ROB;
public :
	ROB(int no);
}

#endif