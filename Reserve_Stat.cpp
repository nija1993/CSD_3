/* Definition of Reservation Station */

#include "Reserve_Stat.h"
#include <iostream>

using namespace std;

/* Constructor for resevation station entry */
Reserve_Entry::Reserve_Entry(int op, int s1, int s2, int d){
	exec_status = false;
	op_code = op;
	src1 = s1;
	src2 = s2;
	dest = d;
}

/* Constructor for Reservation station */
Reserve_Stat::Reserve_Stat(int no){
	no_entries = no;
	a = (reserve_entry*)malloc(no * sizeof(reserve_entry)));
}

/* Poll rrf table to find out if the a particular instruction is ready for execution */
bool Reserve_Stat::poll_rrf(int reg_no){
	
}
