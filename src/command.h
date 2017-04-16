#ifndef CODER_H
#define CODER_H

#include <stdio.h>

#include "command.h"

int encode_file(const char *in_file_name, const char *out_file_name);

int decode_file(const char *in_file_name, const char *out_file_name);

#endif