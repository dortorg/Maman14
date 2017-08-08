/*
 * Assembler.h
 *
 *  Created on: Jul 4, 2017
 *      Author: Dor
 */

#include "MemoryTable.h"
#include "SymbolHash.h"
#include "Utils.h"

typedef struct Databases
{
	Symbol_hash* symbol_hash;
	Memory_table *code;
	Memory_table *data;
	Command commands[MAX_LINE_SIZE];

}Databases;

Databases* first_pass(File_content f);

Memory_table second_pass(Databases databases);

void writeToObj(char* file_name, Memory_table table);

state handleSymbole(Databases** database, Command comm);

state handleCommand(Databases** database, Command comm);

state handleGuidance(Databases** database, Command comm);

state handleString(Databases** database, Command comm);

state handleEntry(Databases** database, Command comm);

state handleData(Databases** database, Command comm);

state handleMat(Databases** database, Command comm);

state handleExtern(Databases** database, Command comm);
