/*
 * utils.c
 *
 *  Created on: Jul 4, 2017
 *      Author: Dor
 */

#include <stdlib.h>
#include "Utils.h"


Bool isEmptyLine(const char *s) {
  static const char *emptyline_detector = " \t\n";

  return strspn(s, emptyline_detector) == strlen(s);
}

void remove_spaces(char* source)
{
	char *write = source, *read = source;
	do {
	   // Skip space and tab
	   if (*read != ' ' && *read != '\t' && *read != '\n')
	       *(write++) = *read;
	} while (*(read++));
}

state fill_content(int argc, char* argv[], File_content* file)
{
	FILE *asm_file;
	char str[MAX_LINE_SIZE];
 /*	if(argc != 2)
 	{
 		return FILE_NOT_EXISTS;
 	}*/
/* 	else
 	{*/
 		if((asm_file = fopen("dor"/*argv[1]*/,"r")) == NULL)
 		{
 			return FILE_NOT_EXISTS;
 		}

 		file->number_of_lines = 0;
 		while(fgets(str, MAX_LINE_SIZE, asm_file) != NULL)
 		{
 			if(isEmptyLine(str) == FALSE && isComment(str) == FALSE)
 			{
 				strcpy(file->content[file->number_of_lines++], str);
 			}
 		}
 	//}
 	return SUCCESS;
}

Bool isComment(char* str)
{
	if(str != NULL)
	{
		if(str[0] != ';')
		{
			return FALSE;
		}
	}
	return TRUE;
}


Command* initCommands(File_content f)
{
	char* token;
	int count = 0;
	int count_command = 0;
	Command* com = (Command*)malloc(sizeof(Command) * f.number_of_lines);
	while(count_command < f.number_of_lines)
	{
		if(isEmptyLine(f.content[count_command]) == FALSE && isComment(f.content[count_command]) == FALSE)
		{
			token = strtok(f.content[count_command], " \n\t");
			strncpy(com[count].command, token, strlen(token) + 1);
			com[count].command[strlen(token) + 1] = '\0';
			token = strtok(NULL, "\n");

			if(token != NULL)
			{
				printf("here\n");
				strncpy(com[count].args, token, MAX_LINE_SIZE);
			}
			else
			{
				strncpy(com[count].args, "\0", 1);
			}
			count++;
		}
		count_command++;
	}
	return com;
}

Bool ifCommand(char* name)
{
	int i;
	for(i = 0; i < COMMANDS_NUMBER; ++i)
	{
		if(strcmp(comms[i].name, name) == 0)
		{
			return TRUE;
		}
	}
	return FALSE;
}

void printError()
{
	printf("%s", errorMsgs[error.line_number]);
	printf("line number %d : %s", error.line_number, error.line);
}


enum LINE_TYPE lineType(char* line)
{
	int i;
	if(ifCommand(line) == TRUE)
	{
		return COMMAND;
	}
	if(line[strlen(line) - 1] == ':')
	{
		return SYMBOL;
	}

	for(i = 0; i < 5; i++)
	{
		if(strcmp(GUIDANCE_LINE[i], line) == 0)
		{
			return GUIDANCE;
		}
	}
	return ERROR;
}

void setError(state s, int line, char* name)
{
	error.status = s;
	error.line_number = line;
	strcpy(error.line, name);
}

state checkCommand(Command* comm)
{
	int i;
	comm->arg1 = strtok(comm->args, ",\n");
	comm->arg2 = strtok(NULL, ",\n");
	printf("%s\n", comm->arg2);
	for(i = 0; i < COMMANDS_NUMBER; ++i)
	{
		if(strcmp(comms[i].name, comm->command) == 0)
		{
			break;
		}
	}
	if(i == COMMANDS_NUMBER)
	{
		return INVALID_COMMAND;
	}else if(comm->arg1 == NULL && comms[i].funcParam != 0)
	{
		return INVALID_ARGS;
	}else if(comm->arg2 == NULL && comms[i].funcParam != 1)
	{
		return INVALID_ARGS;
	}else if(comm->arg2 != NULL && comms[i].funcParam != 2)
	{
		return INVALID_ARGS;
	}
	comm->number_of_args = comms[i].funcParam;
	return SUCCESS;
}
