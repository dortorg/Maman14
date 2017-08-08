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
	Command *commands ;
	state s = SUCCESS;
	Databases* database = (Databases*)malloc(sizeof(Databases));
	(database)->code = create_Memory_Table(100);
	database->data = create_Memory_Table(0);

	//go over the content of the file and create arr of comands
	commands = initCommands(f);

	database->symbol_hash = ht_create( 65536 );

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
	if(s != SUCCESS)
	{
		setError(s, i, f.content[i]);
		printError();
		exit(1);
	}

	//for(i = 0; i < database->symbol_hash->size; i++)
	//{
		ht_get(database->symbol_hash,)
		printf("%d\n",i);
		printf("Symbol : %s\n", database->symbol_hash->table[i]->data.name);
		printf("addr %d\n", database->symbol_hash->table[i]->data.address);
	//}





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
	int addr = (*database)->code->address;
	state s = SUCCESS;
	Command new_comm;
	new_comm = createCommand(comm.args);
	switch(lineType(new_comm.command))
	{
	case COMMAND:
		s = handleCommand(database, new_comm);
		if(s == SUCCESS)
		{
			ht_set( (*database)->symbol_hash, temp, temp, FALSE, TRUE, addr);
		}
		break;
	case GUIDANCE:
		ht_set( (*database)->symbol_hash, temp, temp, FALSE, FALSE,(*database)->data->address);
		s = handleGuidance(database, new_comm);
		break;
	case ERROR:
		s = INVALID_COMMAND;
		break;
	}

	return s;

}

state handleCommand(Databases** database, Command comm)
{
	(*database)->code->address++;
	remove_spaces(comm.args);
	state s = checkCommand(&comm);
	if(comm.number_of_args == 0)
	{
		return SUCCESS;
	}
	else if(comm.number_of_args == 1)
	{
		(*database)->code->address++;
		return SUCCESS;
	}
	else if(comm.number_of_args == 2)
	{
		if(s != SUCCESS)
		{
			return s;
		}
		if(ifReg(comm.arg1) == TRUE && ifReg(comm.arg2) == TRUE)
		{
			(*database)->code->address++;
			return SUCCESS;
		}else if(ifMat(comm.arg1) == TRUE && ifMat(comm.arg2) == FALSE)
		{
			(*database)->code->address+=3;
			return SUCCESS;
		}else if(ifMat(comm.arg1) == TRUE && ifMat(comm.arg2) == TRUE)
		{
			(*database)->code->address+=4;
			return SUCCESS;
		}else
		{
			(*database)->code->address+=2;
			return SUCCESS;
		}
	}
	else
	{
		return INVALID_ARGS;
	}
	return SUCCESS;
}

state handleGuidance(Databases** database, Command comm)
{
	state s = SUCCESS;
	switch(guidanceType(comm.command))
	{
	case EXTERN:
		s = handleExtern(database,  comm);
		break;
	case DATA:
		s = handleData(database,  comm);
		break;
	case ENTRY:
		s = handleEntry(database,  comm);
		break;
	case STRING:
		s = handleString(database,  comm);
		break;
	case MAT:
		s = handleMat(database,  comm);
		break;
	default:
		return INVALID_COMMAND;
	}

	return s;

}

state handleExtern(Databases** database, Command comm)
{
	char temp[80];
	int i = 0;
	if((comm.args[i] >= '0' && comm.args[i] <= '9'))
	{
		return INVALID_ARGS;
	}
	while(comm.args[i] != '\0')
	{
		if(!((comm.args[i] >= 'a' && comm.args[i] <= 'z') || (comm.args[i] >= 'A' && comm.args[i] <= 'Z') ||
				(comm.args[i] >= '0' && comm.args[i] <= '9')))
		{
			return INVALID_ARGS;
		}
		i++;
	}
	temp[i] = '\0';
	ht_set( (*database)->symbol_hash, temp, temp, TRUE, FALSE, 0);
	return SUCCESS;
}

state handleData(Databases** database, Command comm)
{
	int num ;
	int i = 0;
	char* temp;
	temp = strtok(comm.args, ",\n");
	while(temp != NULL)
	{
		for(i = 0; i < strlen(temp); i++)
		{
			if(!(temp[i] >= '0' && temp[i] <= '9'))
			{
				return INVALID_ARGS;
			}
		}
		num = atoi(temp);
		(*database)->data->words[(*database)->data->address].addr = (*database)->data->address;
		(*database)->data->words[(*database)->data->address].data = num;
		(*database)->data->address++;

		temp = strtok(NULL, ",\n");
	}
	return SUCCESS;
}

state handleEntry(Databases** database, Command comm)
{
	return SUCCESS;
}

state handleMat(Databases** database, Command comm)
{
	int size = 0;
	int count = 0;
	char str[20];
	int j = 0;
	int i = 0;
	char *temp;
	if(comm.args[0] == '[')
	{
		i++;
		while(comm.args[i] != ']' && comm.args[i] != '\0' &&
				(comm.args[i] >= '0' && comm.args[i] <= '9'))
		{
			str[j++] = comm.args[i];
			i++;
		}
		if(comm.args[i] != ']')
		{
			return INVALID_ARGS;
		}
		else
		{
			str[j] = '\0';
			size += atoi(str);
			i++;
			if(comm.args[i] != '[')
			{
				return INVALID_ARGS;
			}
			else
			{
				i++;
				j = 0;
				while(comm.args[i] != ']' && comm.args[i] != '\0' &&
						(comm.args[i] >= '0' && comm.args[i] <= '9'))
				{
					str[j] = comm.args[i];
					i++;
					j++;
				}
				if(comm.args[i] != ']')
				{
					return INVALID_ARGS;
				}
				else
				{
					str[j] = '\0';
					size += atoi(str);
					i++;
					temp = strtok(comm.args + i, ",\n");
					while(temp != NULL)
					{
						int number = atoi(temp);
						(*database)->data->words[(*database)->data->address].addr = (*database)->data->address;
						(*database)->data->words[(*database)->data->address].data = number;
						(*database)->data->address++;
						temp = strtok(NULL, ",\n");
						count++;
					}
					if(count > size)
					{
						return INVALID_ARGS;
					}

				}
			}
		}

	}
	else
	{
		return INVALID_ARGS;
	}
}

state handleString(Databases** database, Command comm)
{
	int i = 0;
	int j = 0;
	char str[40];
	if(comm.args[i] != '"')
	{
		return INVALID_ARGS;
	}
	else
	{
		i++;
		while(comm.args[i] != '"' && comm.args[i] != '\0')
		{
			str[j++] = comm.args[i];
			i++;
		}
		if(comm.args[i] != '"')
		{
			return INVALID_ARGS;
		}
		else
		{
			str[j] = '\0';
		}
	}
	i = 0;
	while(str[i] != '\0')
	{
		(*database)->data->words[(*database)->data->address].addr = (*database)->data->address;
		(*database)->data->words[(*database)->data->address].data = str[i];
		(*database)->data->address++;
		i++;
	}
	(*database)->data->words[(*database)->data->address].addr = (*database)->data->address;
	(*database)->data->words[(*database)->data->address].data = 0;
	(*database)->data->address++;
	return SUCCESS;
}


