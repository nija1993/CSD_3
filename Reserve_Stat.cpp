/* Definition of Reservation Station */

#include "Reserve_Stat.h"

using namespace std;

/* Constructor for resevation station entry */
Reserve_Entry::Reserve_Entry(){
	exec_start = EXEC_NOT_STARTED;
	op_code = 0;
	src1_tag = 0;
	src1_value = 0;
	src2_tag = 0;
	src2_value = 0;
	dest_tag = 0;
	dest_value = 0;
}

/* Constructor for Reservation station */
Reserve_Stat::Reserve_Stat(int no){
	no_entries = no;
	reserve_station = (Reserve_Entry*)malloc(no * sizeof(Reserve_Entry)));
}

/* Poll rrf table to find out if the a particular instruction is ready for execution */
bool Reserve_Stat::poll_rrf(int reg_no){
	
}
