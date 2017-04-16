#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "command.h"

//#define OPTION1 ">"
//#define OPTION2 "<"

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

void terms_of_use(){
	puts("Usage:\n"
		"convert <in-file-name> -t <out-file-name>\n"
		"convert <in-file-name> t- <out-file-name>\n");
}

int option_selection(char ** argv){
	if(!strcmp(argv[2], "-t")) {
		puts("convert <in-file-name> -t <out-file-name>");
		if(encode_file(argv[1],argv[3])) {
			return -1;
		}
	}
	else if(!strcmp(argv[2], "t-")) {
		puts("convert <in-file-name> t- <out-file-name>");
		if(decode_file(argv[1],argv[3])) {
			return -1;
		}
	} else {
		terms_of_use();
	}
	return 0;
}

void input_validation(int argc){
	if(argc != 4) {
		terms_of_use();
		exit(EXIT_FAILURE);
	}
}
