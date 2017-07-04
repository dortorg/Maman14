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
	uint count_words;
	word words[MAX_NUMBER_OF_LINES];
}Memory_table;


Memory_table* create_database(uint starting_addr);

state add(Memory_table* memory_table, int field);




#endif /* MEMORYTABLE_H_ */
