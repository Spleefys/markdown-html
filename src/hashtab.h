#ifndef HASHTAB_H
#define HASHTAB_H

#define HASH_MUL 31 
#define HASH_SIZE 5


#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <stdlib.h>

typedef struct listnode {
	char * key;
	struct {
		char * open;
		char * close;  
	}tag;
	struct listnode * next;
}listnode;

unsigned int hashtab_hash_j(char *key, size_t len);

unsigned int hashtab_hash(char *key);  

void hashtab_init(struct listnode **hashtab);

void hashtab_add(listnode **hashtab,char * key, char * open, char * close);

listnode *hashtab_lookup(struct listnode **hashtab, char *key);

void hashtab_delete(struct listnode **hashtab, char *key);

#endif