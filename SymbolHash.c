/*
 * SymbolHash.c
 *
 *  Created on: Jul 3, 2017
 *      Author: Dor
 */


#include "SymbolHash.h"
#include "Utils.h"



/* Create a new hashtable. */
Symbol_hash *ht_create( int size ) {

	Symbol_hash *hashtable = NULL;
	int i;

	if( size < 1 ) return NULL;

	/* Allocate the table itself. */
	if( ( hashtable = malloc( sizeof( Symbol_hash ) ) ) == NULL ) {
		return NULL;
	}

	/* Allocate pointers to the head nodes. */
	if( ( hashtable->table = malloc( sizeof( entry_t * ) * size ) ) == NULL ) {
		return NULL;
	}
	for( i = 0; i < size; i++ ) {
		hashtable->table[i] = NULL;
	}

	hashtable->size = size;

	return hashtable;
}

/* Hash a string for a particular hash table. */
int ht_hash( Symbol_hash *hashtable, char *key ) {

	unsigned long int hashval;
	int i = 0;

	/* Convert our string to an integer */
	while( hashval < ULONG_MAX && i < strlen( key ) ) {
		hashval = hashval << 8;
		hashval += key[ i ];
		i++;
	}

	return hashval % hashtable->size;
}

/* Create a key-value pair. */
entry_t *ht_newpair( char *key, data_s data) {
	entry_t *newpair;

	if( ( newpair = malloc( sizeof( entry_t ) ) ) == NULL ) {
		return NULL;
	}

	if( ( newpair->key = strdup( key ) ) == NULL ) {
		return NULL;
	}

	if( ( strncpy(newpair->data.name, data.name, MAX_LINE_SIZE) ) == NULL ) {
		return NULL;
	}

	newpair->data.address = data.address;
	newpair->data.external = data.external;
	newpair->data.func = data.func;
	newpair->next = NULL;

	return newpair;
}

/* Insert a key-value pair into a hash table. */
state  ht_set( Symbol_hash *hashtable, char *key, char *name, Bool ext, Bool func, uint addr ) {
	int bin = 0;
	data_s data;
	entry_t *newpair = NULL;
	entry_t *next = NULL;
	entry_t *last = NULL;


	data.address = addr;
	data.external = ext;
	data.func = func;
	strncpy(data.name, name, 79);

	bin = ht_hash( hashtable, key );

	next = hashtable->table[ bin ];

	while( next != NULL && next->key != NULL && strcmp( key, next->key ) > 0 ) {
		last = next;
		next = next->next;
	}

	/* There's already a pair.  Let's replace that string. */
	if( next != NULL && next->key != NULL && strcmp( key, next->key ) == 0 ) {

		return SYMBOL_EXIST;

	/* Nope, could't find it.  Time to grow a pair. */
	} else {
		newpair = ht_newpair( key, data );

		/* We're at the start of the linked list in this bin. */
		if( next == hashtable->table[ bin ] ) {
			newpair->next = next;
			hashtable->table[ bin ] = newpair;

		/* We're at the end of the linked list in this bin. */
		} else if ( next == NULL ) {
			last->next = newpair;

		/* We're in the middle of the list. */
		} else  {
			newpair->next = next;
			last->next = newpair;
		}
	}
	return SUCCESS;
}

/* Retrieve a key-value pair from a hash table. */
data_s* ht_get( Symbol_hash *hashtable, char *key ) {
	int bin = 0;
	entry_t *pair;

	bin = ht_hash( hashtable, key );

	/* Step through the bin, looking for our value. */
	pair = hashtable->table[ bin ];
	while( pair != NULL && pair->key != NULL && strcmp( key, pair->key ) > 0 ) {
		pair = pair->next;
	}

	/* Did we actually find anything? */
	if( pair == NULL || pair->key == NULL || strcmp( key, pair->key ) != 0 ) {
		return NULL;

	} else {
		return &pair->data;
	}

}
