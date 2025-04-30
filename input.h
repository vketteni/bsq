#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>

// Forward declaration: we don't need full definition here
typedef struct ParsingContext ParsingContext;

int parse_header(ParsingContext *ctx);
int parse_body(ParsingContext *ctx);
FILE *open_input(const char *file_path);

int line_format_valid(ParsingContext *ctx);
int dp_and_cols_init(ParsingContext *ctx);
int line_to_map_append(ParsingContext *ctx);

#endif

