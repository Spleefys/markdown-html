#ifndef CODER_H
#define CODER_H

#include <stdio.h>

#include "command.h"

#include "hashtab.h"


void build_paragraph(FILE * in, FILE * out, listnode ** hashtab_md);

void print_open_tag(char * word, FILE * out, int length);

void print_close_tag(char * word, FILE * out, int length);

void print_str(char * buff,char * word, FILE * out, int k ,listnode ** hashtab, int l);

void build_headers(FILE * in, FILE * out, listnode ** hashtab);

void check_in(char * word, FILE * in, FILE * out, listnode ** hashtab);

int encode_file(const char *in_file_name, const char *out_file_name, listnode ** hashtab);

int decode_file(const char *in_file_name, const char *out_file_name);

void terms_of_use();

int option_selection(char ** argv, listnode ** hashtab);

void input_validation(int argc);

#endif