/*
 * utils.h
 *
 *  Created on: Jul 3, 2017
 *      Author: Dor
 */

#ifndef UTILS_H_
#define UTILS_H_

#ifndef NULL
#define NULL   ((void *) 0)
#endif

#include <stdio.h>
#include <string.h>

#define MAX_LINE_SIZE 80
#define MAX_NUMBER_OF_LINES 256

typedef unsigned int uint;

typedef struct word
{
	uint addr;
	unsigned int data:10;
}word;

typedef struct command
{

	int number_of_args;
	char command[80];
}Command;

typedef struct File_content
{
	int number_of_lines;
	char content[MAX_NUMBER_OF_LINES][MAX_LINE_SIZE];
}File_content;

typedef enum Bool {FALSE, TRUE} Bool;

typedef enum state {SYMBOL_EXIST, FILE_NOT_EXISTS, SUCCESS} state;

static state status;

Bool isEmptyLine(const char *s);

void remove_spaces(char* source);

state fill_content(char* file_name, File_content* file);

#endif /* UTILS_H_ */
