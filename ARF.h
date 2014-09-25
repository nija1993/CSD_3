/* Declaration of ARF */

#ifndef ARF_H  
#define ARF_H

#include <stdint.h>

class ARF_Entry {
	bool busy;
	int tag;
	uint64_t value;
public :
	ARF_Entry();
	void commit(uint64_t value); 
};

class ARF {
	ARF_Entry* arf;
	int no_entries;
public : 
	ARF(int no);
};

#endif
