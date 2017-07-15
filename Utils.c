/*
 * utils.c
 *
 *  Created on: Jul 4, 2017
 *      Author: Dor
 */

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
 			if(isEmptyLine(str) == FALSE)
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


 int initCommands(File_content f, Command** commands)
{
	char* token;
	int count = 0;
	int count_command = 0;
	while(count_command < f.number_of_lines)
	{
		if(isEmptyLine(f.content[count_command]) == FALSE && isComment(f.content[count_command]) == FALSE)
		{
			printf("%s\n",f.content[count_command]);
	 		printf("initCommands1\n");

			token = strtok(f.content[count_command], " \n\t");
			printf("initCommands2\n");
			printf("%s\n",token);
			strncpy(commands[count]->command, token, MAX_LINE_SIZE);


			remove_spaces(commands[count]->command);
	 		printf("initCommands3\n");

			token = strtok(NULL, "\n");
	 		printf("initCommands4\n");

			if(token != NULL)
			{
				strncpy(commands[count]->args, token, MAX_LINE_SIZE);
		 		printf("initCommands5\n");

				remove_spaces(commands[count]->args);
		 		printf("initCommands6\n");
			}
			else
			{
		 		printf("initCommands7\n");

				strncpy(commands[count]->args, "\0", MAX_LINE_SIZE);
		 		printf("initCommands8\n");

			}
			count++;
		}
		count_command++;
	}
	return count;
}
