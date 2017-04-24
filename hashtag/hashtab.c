#include "hashtab.h"


unsigned int hashtab_hash(char * key) {
	unsigned int h = 0;
	char * p;

	for(p = key;*p != '\0';p++)
			h = (unsigned int)*p + h;
			//h = h * HASH_MUL;
	return h % 11;
}

uint32_t hashtab_hash_j(char *key, size_t len){
	uint32_t hash, i;
	for(hash = i = 0; i < len; ++i) {
		hash += key[i];
		hash += (hash << 10);
		hash ^= (hash >> 6);
	}
	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash <<15);
	return hash % HASH_SIZE;
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
    //uint32_t index = hashtab_hash_j(key, strlen(key));
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
	int index;
	listnode * node;
	index = hashtab_hash(key);
	//uint32_t index = hashtab_hash_j(key, strlen(key));
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

/*void free_hashtab(listnode **e) {
    free((*e)->key);
    free((*e)->value);
    free(*e);
    *e = NULL;
}

void delete_hashtab(Hashmap **map) {
    listnode *map = *map;
    size_t i, size;
    Node *anchor = NULL;    //текущий узел
    Node *target = NULL;    //предыдущий узел
 
    size = map->arr_size;
     
    for (i = 0; i < size; i++) {
        anchor = map->data[i];
        while (anchor) {
            target = anchor;
            anchor = anchor->next;
            FREE_ENTRY(&(target->value));
            free(target);           
        }
        free(anchor);
    }
     
    free(map->data);
    free(*map);
    *map = NULL;
}*/
