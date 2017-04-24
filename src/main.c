#include "command.h"
#include "hashtab.h"


int main(int argc, char **argv) {
	input_validation(argc);

	FILE *file;
	
	int i ,j;
	i = j = 0;
	
	char ** word;
	word = malloc(sizeof(char*)*5);
	for(int i = 0 ;i < 5; i++)
		word[i]= malloc(sizeof(char)*5);

	file = fopen("md.txt", "r");

	listnode *hashtab_md[HASH_SIZE];

	hashtab_init(hashtab_md);

	while (fscanf (file, "%s", word[i])!= EOF) {
		printf("%d : %s\n", i, word[i]);
		i++;
	}
	 
	hashtab_add(hashtab_md, word[0], "<h1>" ,"</h1>");
	hashtab_add(hashtab_md, word[1], "<h2>" ,"</h2>");
	hashtab_add(hashtab_md, word[2], "<h3>" ,"</h3>");
	hashtab_add(hashtab_md, word[3], "<h4>" ,"</h4>");
	hashtab_add(hashtab_md, word[4], "<p>" ,"</p>");
	
	
	option_selection(argv, hashtab_md);

	for(j = 0; j < 5; j++) {
		hashtab_delete(hashtab_md, word[j]);
		j++;
    }

	
	fclose(file);
	return 0;
}
