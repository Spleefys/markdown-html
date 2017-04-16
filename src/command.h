#ifndef CODER_H
#define CODER_H

#include <stdio.h>

#include "command.h"

int encode_file(const char *in_file_name, const char *out_file_name);

int decode_file(const char *in_file_name, const char *out_file_name);

void terms_of_use();

int option_selection(char ** argv);

void input_validation(int argc);

#endif