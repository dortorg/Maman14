/*
 * Assembler.c
 *
 *  Created on: Jul 4, 2017
 *      Author: Dor
 */

#include "utils.h"


void main()
{
	File_content f;
	fill_content("dor", &f);
	printf("%d \n", f.number_of_lines);
	printf("%s \n", f.content[0]);

}

