/*
 * utils.c
 *
 *  Created on: Jul 4, 2017
 *      Author: Dor
 */

#include "utils.h"


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

state fill_content(char* file_name, File_content* file)
{
	FILE *asm_file;
	char str[MAX_LINE_SIZE];
	if((asm_file = fopen(file_name,"r")) == NULL)
	{
		return FILE_NOT_EXISTS;
	}

	file->number_of_lines = 0;
	while(fgets(str, MAX_LINE_SIZE, stdin) != NULL)
	{
		if(isEmptyLine(str) == FALSE)
		{
			strcpy(file->content[file->number_of_lines++], str);
		}
	}

	return SUCCESS;
}
