#ifndef STORE_Q_H
#define STORE_Q_H

class Store_Q_Entry {
public:
	int inst_num;
	bool completed;			/*Completed will be set to true when inst is removed from ROB*/
	bool valid;
	int address;
	int value;
	bool to_set_complete;
	Store_Q_Entry();
};

class Store_Q {
public:
	Store_Q_Entry *store;
	int no_entries;
	Store_Q(int no);
	void add_entry(int inst, int addr, int val);
	bool probe(int addr, int inst);
	int search(int addr, int inst);
	bool check_vacancy();
	int remove_least_completed();
	void print();
	bool busy();
	void set_complete();
};

#endif
