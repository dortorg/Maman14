/*
 * SymbolHash.h
 *
 *  Created on: Jul 3, 2017
 *      Author: Dor
 */

#ifndef SYMBOLHASH_H_
#define SYMBOLHASH_H_

#define _XOPEN_SOURCE 500 /* Enable certain library functions (strdup) on linux.  See feature_test_macros(7) */

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include "Utils.h"

typedef struct data_s {
	 Bool external;
	 Bool func;
	 char name[MAX_LINE_SIZE];
	 uint address;
}data_s;

struct entry_s {
	char *key;
	data_s data;
	struct entry_s *next;
};

typedef struct entry_s entry_t;

typedef struct symbol_hash {
	int size;
	struct entry_s **table;
}Symbol_hash;



Symbol_hash *ht_create( int size );

int ht_hash( Symbol_hash *hashtable, char *key );

entry_t *ht_newpair( char *key, data_s data);

state  ht_set( Symbol_hash *hashtable, char *key, char *name, Bool ext, Bool func, uint addr );

data_s* ht_get( Symbol_hash *hashtable, char *key );

#endif /* SYMBOLHASH_H_ */
