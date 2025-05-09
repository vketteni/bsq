#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>

// Forward declaration: we don't need full definition here
typedef struct ParsingContext ParsingContext;

int parse_header(ParsingContext *ctx);
int parse_body(ParsingContext *ctx);
FILE *open_input(const char *file_path);

int valid_line_format(ParsingContext *ctx, size_t line_index);
int append_line_to_map(ParsingContext *ctx);

#endif

