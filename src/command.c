#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "command.h"
#include "hashtab.h"


void print_open_tag(char * word, FILE * out, int length){
	for (int i = 0 ;i < length ; i++)
		fprintf(out, "%c", word[i]);
}

void print_close_tag(char * word, FILE * out, int length){
	for (int i = 0 ;i < length; i++)
		fprintf(out, "%c", word[i]);
	fprintf(out, "%s", "\n");
}


void print_str(char * buff,char * word, FILE * out, int k , listnode ** hashtab_md, int l){
	int i = 0;
	listnode * node = hashtab_lookup(hashtab_md, word);
	print_open_tag(node->tag.open, out, strlen(node->tag.open));
	for (i = l ; i < k ; i++){
		if (buff[i] == '\n' ||buff[i] == EOF)
			continue;
		fprintf(out, "%c", buff[i]);
	}
	print_close_tag(node->tag.close, out, strlen(node->tag.close));

}


void build_headers(FILE * in, FILE * out, listnode ** hashtab_md){
	
	int k = 0;
	int l = 0;
	char * buff;
	buff = malloc(sizeof(char) * 100);

	char * buff_h;
	buff_h = malloc(sizeof(char) * 6); 
	while(1) {
			buff[k] = fgetc(in);
			if(buff[k] == '#') {
				l++;
				k++; 
				continue;
			}
			if(buff[k] == '\n') {
				break;
			}
			k++;
		}	
	
	for(int i = 0; i < l + 1 ; i++ )
		buff_h[i] = '#';

	print_str(buff, buff_h, out, k, hashtab_md, l);
	//fseek(in, 1 ,SEEK_CUR);
	free(buff_h);
	free(buff);
}

void build_paragraph(FILE * in, FILE * out, listnode ** hashtab_md) {
	int k = 0;
	char * buff;
	buff = malloc(sizeof(char) * 256);
	memset(buff, 0, 256);
	while((buff[k] = fgetc(in)) == '\n')
		k++;
	if(k != 0) {
		fseek(in, -1 ,SEEK_CUR);
		fprintf(out, "%c", buff[k-1]);
	}
	else
		fseek(in, -1 ,SEEK_CUR);
	while(1) {	
		buff[k] = fgetc(in);
		if(buff[k] == EOF) {
			break;	
		}
		if(buff[k] == '\n') {
			buff[k+1] = fgetc(in);
			if(buff[k+1] == '\n') {
				fseek(in, -1 ,SEEK_CUR);
				buff[k+1] = 0;
				break;
			}
			else {
				fseek(in, -1 ,SEEK_CUR);
				buff[k+1] = 0;
				continue;
			}
		}
		k++;	
	}


	
	print_str(buff, "\\n", out, k, hashtab_md, 0); 

	free(buff);	

}

/*void build_paragraph(FILE * in, FILE * out, listnode ** hashtab_md) {
	int k = 0;
	char * buff;
	buff = malloc(sizeof(char) * 256);
	//int count = 1;
	memset(buff, 0, 256);
	while((buff[k] = fgetc(in)) == '\n') {
		fprintf(out, "%c", buff[k]);
		k++;
	}


	fseek(in, -1 ,SEEK_CUR);
	//fprintf(out, "%c", buff[k-1]);
	memset(buff, 0, k);
	k = 0;
	buff[k] = fgetc(in);
	k++;
	while(1) {	
		buff[k] = fgetc(in);
		if(buff[k] == EOF)
			break;	
		if(buff[k] == '\n') {
			fseek(in, -1 ,SEEK_CUR);
			break;
		}
		else {
			k++;
			buff[k] = fgetc(in);
		}
	k++;	

	}
	print_str(buff, "\\n", out, k, hashtab_md, 0); 

	free(buff);	
}*/


void check_in(char * word, FILE * in, FILE * out, listnode ** hashtab_md){
	listnode * node = hashtab_lookup(hashtab_md, word);
	if(!node)
		return;
	if(!strcmp(node->key, word)) {
		if(!strcmp(word, "#")){
			build_headers(in, out, hashtab_md);
			return;
		}
		if(!strcmp(word, "\\n")) {
			build_paragraph(in, out, hashtab_md);
			return;
		}
	}
}


int encode_file(const char *in_file_name, const char *out_file_name, listnode ** hashtab_md) {

	FILE *in = fopen(in_file_name, "r");

	if(!in){
		perror("Carefully, happened error ");
		return -1;
	}

	FILE *out = fopen(out_file_name, "w");

	if(!out) {
		perror("Carefully, happened error ");
		return -1;
	}

	char ** word;
	word = malloc(sizeof(char*) * 10);
	for (int i = 0; i < 10; i++) {
		word[i] =  malloc(sizeof(char)*50);
	}
	
	
	for (int i = 0; i < 3 ; i++) {
		for(int j = 0; j < 7; j++) {
			if(feof(in)) {
				break;
			}
			word[i][j] = fgetc(in);
			if(word[i][j] == '#') {
				check_in(&word[i][j], in, out, hashtab_md);
			}
			check_in("\\n", in, out, hashtab_md);
				
			//check_in(&word[i][j], in, out, hashtab_md);
		}
	}
	
	for (int i = 0; i < 10; i++) {
		free(word[i]);
	}
	
	free(word);
	
	fclose(out);
	fclose(in);

	return 0;
}

int decode_file(const char *in_file_name, const char *out_file_name)
{
	FILE *in = fopen(in_file_name, "r");

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

int option_selection(char ** argv, listnode ** hashtab_md){
	if(!strcmp(argv[2], "-t")) {
		puts("convert <in-file-name> -t <out-file-name>");
		if(encode_file(argv[1],argv[3], hashtab_md)) {
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
