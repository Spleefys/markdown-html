#include <stdio.h>
#include <stdlib.h>
#include "command.h"

int encode_file(const char *in_file_name, const char *out_file_name) {

	FILE *in = fopen(in_file_name, "r");
	
	if(!in){
		perror("Carefully, happened error ");
		return -1;
	}
	
	FILE *out = fopen(out_file_name, "w+");
	
	if(!out) {
		perror("Carefully, happened error ");
		return -1;
	}

	char ** word;
	int i = 0;
	word = (char**) malloc(sizeof(char*) * 10);
	for (i = 0; i < 3; i++) {
        word[i] = (char*) malloc(10 * sizeof(char));
    }

	for (i = 0; i < 3; i++) {
        fgets(word[i], sizeof(word)*10, in);
    }
	
	for (i = 0; i < 3; i++) {
        fprintf(out, "%s", word[i]);
    }

	
	
	fclose(out);
	fclose(in);

	return 0;
}


int decode_file(const char *in_file_name, const char *out_file_name)
{
	FILE *in = fopen(in_file_name, "rb");
	
	if(!in){
		perror("Carefully, happened error ");
		return -1;
	}
	FILE *out = fopen(out_file_name, "w");
	
	if(!out) {
		perror("Carefully, happened error ");
		return -1;
	}

	


	fclose(out);
	fclose(in);
	return 0;
}