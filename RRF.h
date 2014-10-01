/* Declaration of RRF */

#ifndef RRF_H  
#define RRF_H
#include <stdint.h>

/* Final commit is committing from RRF to ARF */
class RRF_Entry {
public :
	bool busy, valid;
	uint64_t value;
	RRF_Entry();
};

class RRF {
	int no_entries;
	int no_occ; 
	public :
		RRF_Entry* rrf; 
		RRF(int no);
		bool file_status();
		bool check_entry_arf();
		int add_entry();
		void update(int index, uint64_t result);
		void print();
};

#endif
