/* Declaration of Reservation Station */

#ifndef RESERVE_STAT_H  
#define RESERVE_STAT_H

#define ADD 1
#define SUB 2
#define MUL 3
#define DIV 4

class Reserve_Entry {
	int op_code;
	int src1, src2, dest;
	bool exec_status;
public :
	Reserve_Entry(int op, int s1, int s2, int d);
}

class Reserve_Stat {
	Reserve_Entry* reserve_station;
	int no_entries;
	public : 
		Reserve_Stat(int no);
		bool poll_arf(int x);
}
