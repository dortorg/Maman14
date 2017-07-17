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
#define COMMANDS_NUMBER 16

typedef unsigned int uint;

typedef struct word
{
	uint addr;
	unsigned int ERA:2;
	unsigned int des:2;
	unsigned int source:2;
	unsigned int opcode:4;

}word;

typedef struct command
{
	int number_of_args;
	char args[MAX_LINE_SIZE];
	char command[MAX_LINE_SIZE];
}Command;

typedef struct File_content
{
	int number_of_lines;
	char content[MAX_NUMBER_OF_LINES][MAX_LINE_SIZE];
}File_content;

enum args {NONE, ONE, TWO};

enum {MOV, CMP, ADD, SUB, NOT, CLR,
	LEA, INC, DEC, JMP, BNE, RED, PRN,
	JSR, RTS, STOP};

static struct Functions{
    char *name;
    int code : 3;
    int funcParam;
}funcs[] = {
    {"mov", MOV, TWO},
    {"cmp", CMP, TWO},
    {"add", ADD, TWO},
    {"sub", SUB, TWO},
    {"not", NOT, ONE},
    {"clr", CLR, ONE},
    {"lea", LEA, TWO},
    {"inc", INC, ONE},
    {"dec", DEC, ONE},
	{"jmp", JMP, ONE},
	{"bne", BNE, ONE},
	{"red", RED, ONE},
	{"prn", PRN, ONE},
	{"jsr", JSR, ONE},
	{"rts", RTS, NONE},
	{"stop", STOP, NONE}
};

typedef enum Bool {FALSE, TRUE} Bool;

typedef enum state {SYMBOL_EXIST, FILE_NOT_EXISTS, INVALID_COMMAND, INVALID_ARGS, SUCCESS} state;

static state status;

/*List: Errors*/
static char *errorMsgs[] = {
    "*ERROR: Symbol exist\n",
    "*ERROR: file not exist\n",
    "*ERROR: invalid command\n",
	"*ERROR: invalid args\n",

};



Bool isEmptyLine(const char *s);

void remove_spaces(char* source);

state fill_content(int argc, char* argv[], File_content* file);

Bool isComment(char* str);

Command* initCommands(File_content f);

int commandExist(char* name);

void printError();

#endif /* UTILS_H_ */
