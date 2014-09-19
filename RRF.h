/* Declaration of RRF */

#ifndef RRF_H  
#define RRF_H

class RRF_Entry {
	bool busy, valid;
	int offset, arf_entry;
	uint64_t value; 
public :
	RRF_Entry(int offs, int arf_e);
	void commit(uint64_t value); 
}

class RRF {
	RRF_Entry* rrf;
	int no_entries;
	public : 
		RRF(int no);
		bool check_entry_arf();
}

#endif