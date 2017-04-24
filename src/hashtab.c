#include "hashtab.h"


unsigned int hashtab_hash(char * key) {
	unsigned int h = 0;
	char * p;

	for(p = key;*p != '\0';p++)
			h = (unsigned int)*p + h;
	return h % 11;
}

void hashtab_init(struct listnode **hashtab) {
	int i;
	for(i = 0; i < HASH_SIZE;i++) {
		hashtab[i] = NULL;
	}

}

void hashtab_add(listnode **hashtab,char *key, char * open, char * close) {
	listnode *node;
	int index = hashtab_hash(key);
	node = malloc(sizeof(*node));
	if(node) {
		node->key = key;
		node->tag.open = open;
		node->tag.close = close;
		node->next = hashtab[index];
		hashtab[index] = node;

	}
}

listnode *hashtab_lookup(listnode **hashtab, char * key) {
	listnode * node;
	int index = hashtab_hash(key);
	for(node = hashtab[index]; node != NULL; node = node->next) {
		if(strcmp(node->key, key) == 0) {
			return node;
		}
	}
	return NULL;
}

void hashtab_delete(struct listnode **hashtab, char *key){
	int index;
	listnode * p, *prev = NULL;

	index = hashtab_hash(key);
	for(p = hashtab[index]; p != NULL; p = p->next) {
		if (strcmp(p->key, key) == 0) {
			if (prev == NULL)
				hashtab[index] = p->next;
			else
				prev->next = p->next;
			free(p);
			return;
		}
		prev = p;
	}
}
