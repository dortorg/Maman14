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
#include "utils.h"

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

struct hashtable_s {
	int size;
	struct entry_s **table;
};

typedef struct hashtable_s hashtable_t;


hashtable_t *ht_create( int size );

int ht_hash( hashtable_t *hashtable, char *key );

entry_t *ht_newpair( char *key, data_s data);

state  ht_set( hashtable_t *hashtable, char *key, char *name, Bool ext, Bool func, uint addr );

data_s* ht_get( hashtable_t *hashtable, char *key );

#endif /* SYMBOLHASH_H_ */
