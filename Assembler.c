/*
 * Assembler.c
 *
 *  Created on: Jul 4, 2017
 *      Author: Dor
 */

#include "Assembler.h"
#include <stdio.h>
int main(int argc, char* argv[])
{
	File_content f;
	Databases* database;
	Memory_table code_segment;
	char* filename;
	printf("fill_content\n");
	
	if(fill_content(argc, argv, &f) == SUCCESS )
	{
		printf("first_pass\n");

		database = first_pass(f);
	}
	else
	{
		printError();
		exit(1);
	}
	if(error.status == SUCCESS)
	{
		code_segment = second_pass(*database);
		if(error.status == SUCCESS)
		{
			writeToObj(filename, code_segment);
		}
		else
		{
			printError();
			exit(1);
		}
	}
	else
	{
		printError();
		exit(1);
	}
	

	return 0;
}

Databases* first_pass(File_content f)
{
	int i;
	state s = SUCCESS;
	Databases* database = (Databases*)malloc(sizeof(Databases));

	Command *commands ;
	//go over the content of the file and create arr of comands
	commands = initCommands(f);

	for(i = 0; i < f.number_of_lines; ++i)
	{
		if(s == SUCCESS)
		{
			switch(lineType(commands[i].command))
			{
			case SYMBOL:
				s = handleSymbole(&database, commands[i]);
				break;
			case COMMAND:
				s = handleCommand(&database, commands[i]);
				break;
			case GUIDANCE:
				s = handleGuidance(&database, commands[i]);
				break;
			case ERROR:
				setError(INVALID_COMMAND, i, f.content[i]);
				printError();
				exit(1);
				break;
			}

		}
		else
		{
			setError(s, i, f.content[i]);
			printError();
			exit(1);
		}
	}

	// add labels to the table and check if there is not the same label in the table

	//Increment the counter address of the code

	//add data to the data table and increment the counter

	//concat the data table to the end of the code table with the proper address


}


Memory_table second_pass(Databases databases)
{
	//go over the commands

	//when find .entry , write to .ent file the name of the symbol and the address

	//אם המיעון הוא חיצוני אז יש צורך להוסיף לקובץ של  .ext  את השם של המשתנה ביחד עם הכתובת שיש בה שימוש, וזה יתבצע רק לאחר שראינו שהוא קיים בטבלת הסמלים

	//fill the content of the memory table of the code

	//return the memory table after he full
}

void writeToObj(char* file_name, Memory_table table)
{

}

state handleSymbole(Databases** database, Command comm)
{
	char *temp = strtok(comm.command, ":");
	Bool ext, func;
	(*database)->symbol_hash.size++;

	return SUCCESS;

}

state handleCommand(Databases** database, Command comm)
{
	char* arg1, arg2;
	int i = 0;
	(*database)->code.count_words++;
	remove_spaces(comm.args);
	state s = checkCommand(&comm);
	if(comm.number_of_args == 0)
	{
		return SUCCESS;
	}
	else if(comm.number_of_args == 1)
	{
		(*database)->code.count_words++;
		return SUCCESS;
	}
	else if(comm.number_of_args == 2)
	{

		if(s != SUCCESS)
		{
			return s;
		}
		arg1 = strtok(comm.args, ",");
		arg2 = strtok(NULL, ",");
	}
	else
	{
		return INVALID_ARGS;
	}
	return SUCCESS;
}
state handleGuidance(Databases** database, Command comm)
{
	return SUCCESS;

}


