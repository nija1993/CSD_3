/* Definition of Reservation Station */

#include "Reserve_Stat.h"
#include <stdlib.h>

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
	first_unocc = 0;
	reserve_station = (Reserve_Entry*)malloc(no * sizeof(Reserve_Entry));
}

/* To add entries to reservation station */
void Reserve_Stat::add_entry(Reserve_Entry entry){
	reserve_station[first_unocc] = entry;
}

/* Returns true if reservation_station has vacancy to accomodate more entries*/
bool Reserve_Stat::array_status(){
	if(first_unocc == no_entries)
		return true;
	else
		return false;
}

/* Poll rrf table to find out if the a particular instruction is ready for execution */
bool Reserve_Stat::poll_rrf(int reg_no){
	return false;	
}

/* Returns if the reservation station is busy or free */
bool Reserve_Stat::busy(){
	if(first_unocc == 0)
		return false;
	else
		return true;
}





