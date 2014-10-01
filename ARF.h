/* Declaration of ARF */

#ifndef ARF_H  
#define ARF_H

#include <stdint.h>

class ARF_Entry {
public :
	bool busy;
	int tag;
	uint64_t value;
	ARF_Entry();
	void commit(uint64_t value); 
};

class ARF {
public : 
	ARF_Entry* arf;
	int no_entries;
	ARF(int no);
	void print();
};

#endif
