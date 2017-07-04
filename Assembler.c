/*
 * Assembler.c
 *
 *  Created on: Jul 4, 2017
 *      Author: Dor
 */

#include "Assembler.h"

void main()
{
	File_content f;
	Databases database;
	Memory_table code_segment;
	char* filename;

	database = first_pass(f);
	if(status == SUCCESS)
	{
		code_segment = second_pass(database);
		if(status == SUCCESS)
		{
			writeToObj(filename, code_segment);
		}
	}
	else
	{
		//TODO PRINT ERROR
	}






}

Databases first_pass(File_content f)
{
	//go over the content of the file and create arr of comands

	//split the command

	//check the command

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
