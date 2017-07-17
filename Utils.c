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
	   if (*read != ' ' && *read != '\t')
	       *(write++) = *read;
	} while (*(read++));
}

state fill_content(int argc, char* argv[], File_content* file)
{
	FILE *asm_file;
	char str[MAX_LINE_SIZE];
 	if(argc != 2)
 	{
 		return FILE_NOT_EXISTS;
 	}
 	else
 	{
 		if((asm_file = fopen(argv[1],"r")) == NULL)
 		{
 			return FILE_NOT_EXISTS;
 		}

 		file->number_of_lines = 0;
 		while(fgets(str, MAX_LINE_SIZE, asm_file) != NULL)
 		{
 			if(isEmptyLine(str) == FALSE && isComment(str) == FALSE)
 			{
 		 		printf("fill_content1\n");
 				strcpy(file->content[file->number_of_lines++], str);
 			}
 		}
 	}
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
			strncpy(com[count].command, token, strlen(token));
			remove_spaces(com[count].command);
			token = strtok(NULL, "\n");

			if(token != NULL)
			{
				strncpy(com[count].args, token, MAX_LINE_SIZE);
				remove_spaces(com[count].args);
			}
			else
			{
				strncpy(com[count].args, "\0", MAX_LINE_SIZE);
			}
			count++;
		}
		count_command++;
	}
	return com;
}

int commandExist(char* name)
{
	int i;
	for(i = 0; i < COMMANDS_NUMBER; ++i)
	{
		if(strcmp(funcs[i].name, name) == 0)
		{
			return i;
		}
	}
	status = INVALID_COMMAND;
	return -1;
}

void printError()
{
	printf("%s", errorMsgs[status]);
}
