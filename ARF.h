/* Declaration of ARF */

#ifndef ARF_H  
#define ARF_H

#include <stdint.h>

class ARF_Entry {
	bool busy;
	int offset, tag;
	uint64_t value;
public :
	ARF_Entry(int offs, int t);
	void commit(uint64_t value);  
};

class ARF {
	ARF_Entry* arf;
	int no_entries;
public : 
	ARF(int no);
};

#endif