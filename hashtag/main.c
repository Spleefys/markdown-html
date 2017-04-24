#include "hashtab.h"


int main(){
	
	FILE *file;
	//FILE *f;
	
	int i ,j;
	i = j = 0;
	
	char ** word;
	word = malloc(sizeof(char*)*5);
	for(int i = 0 ;i < 5; i++)
		word[i]= malloc(sizeof(char)*5);

	file = fopen("md.txt", "r");
	//f = fopen("md.txt", "r");

	listnode *hashtab[HASH_SIZE];

	hashtab_init(hashtab);

	while (fscanf (file, "%s", word[i])!= EOF) {
		printf("%d : %s\n", i, word[i]);
		i++;
	}
	
	hashtab_add(hashtab, word[0], "<h1>" ,"</h1>");
	hashtab_add(hashtab, word[1], "<h2>" ,"</h2>");
	hashtab_add(hashtab, word[2], "<h3>" ,"</h3>");
	hashtab_add(hashtab, word[3], "<h4>" ,"</h4>");
	hashtab_add(hashtab, word[4], "<p>" ,"</p>");

	fseek(file, 0L, SEEK_SET);

	i = 0;
	listnode *node;
	while (fscanf (file, "%s", word[i])!= EOF) {
	    node = hashtab_lookup(hashtab, word[i]);
	    printf("%s : %s %s\n", node->key, node->tag.open, node->tag.close);
	    ++i;
	}
	
	//printf("%s,%d\n", node->key, node->value);

	for(j = 0; j < 5; j++) {
		hashtab_delete(hashtab, word[j]);
		j++;
    }

	fclose(file);
    //fclose(f);
	return 0;
}
