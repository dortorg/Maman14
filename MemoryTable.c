/*
 * Encoding.c
 *
 *  Created on: Jul 4, 2017
 *      Author: Dor
 */
#include "MemoryTable.h"

Memory_table* create_Memory_Table(uint starting_addr)
{
	Memory_table* mem = (Memory_table*)malloc(sizeof(Memory_table));
	mem->address = starting_addr;
	return mem;
}

/*
state add(Memory_table* memory_table, word word)
{

}
*/
