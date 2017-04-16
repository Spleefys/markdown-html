#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "command.h"


//#define OPTION1 ">"
//#define OPTION2 "<"

void terms_of_use(){
	puts("Usage:\n"
		"convert <in-file-name> -t <out-file-name>\n"
		"convert <in-file-name> t- <out-file-name>\n");
}

int option_selection(char ** argv){
	if(!strcmp(argv[2], "-t")) {
        puts("convert <in-file-name> > <out-file-name>\n");
        if(encode_file(argv[1],argv[3])) {
        	return -1;
        } 
	} 
	else if(!strcmp(argv[2], "t-")) {
		puts("convert <in-file-name> < <out-file-name>\n");
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

int main(int argc, char **argv) {
    
    input_validation(argc);
    option_selection(argv);
	
	return 0;
}