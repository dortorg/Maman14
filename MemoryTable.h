/*
 * Encoding.h
 *
 *  Created on: Jul 4, 2017
 *      Author: Dor
 */

#ifndef MEMORYTABLE_H_
#define MEMORYTABLE_H_

#include "Utils.h"


typedef struct Memory_table
{
	uint address;
	word words[MAX_NUMBER_OF_LINES];
}Memory_table;


Memory_table* create_Memory_Table(uint starting_addr);

state add(Memory_table* memory_table, int field);




#endif /* MEMORYTABLE_H_ */
