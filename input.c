#include "input.h"
#include "bsq.h"
#include "utils.h"
#include <stdlib.h>
#include <stdbool.h>

FILE *open_input(const char *file_path) {
	return file_path ? fopen(file_path, "r") : stdin;
}

int parse_header(ParsingContext *ctx) {
    char end;
    int	result;
   
    result	= fscanf(
        ctx->fp,
        "%zu%c%c%c%c",
        &ctx->rows,
        &ctx->symbols[EMPTY],
        &ctx->symbols[OBSTACLE],
        &ctx->symbols[FULL],
        &end
    );
    if (result != 5 || end != '\n' || ctx->rows <= 0) {
        return 0;
    }
    return 1;
}

int parse_body(ParsingContext *ctx) {
    bool firstLine;

    ctx->line = NULL;
    ctx->line_cap = 0;
    ctx->line_len = 0;
    firstLine = true;
    while ((ctx->line_len = getline(&ctx->line, &ctx->line_cap, ctx->fp)) > 0) {
        if (firstLine) {
            ctx->cols = ctx->line_len - 1; // minus one because new line is excluded
            firstLine = false;
        }
        if (!line_format_valid(ctx)) {
            return 0;
        }
        if (!line_to_map_append(ctx)) {
            return 0;
        }
    }
    free(ctx->line);
    ctx->line = NULL;
    return 1;
}

int line_format_valid(ParsingContext *ctx) {
    return ctx->line_len - 1 == ctx->cols; // minus one because new line is excluded
}

int line_to_map_append(ParsingContext *ctx) {
    char    *tmp;
    
    tmp = ctx->map ? ft_strcat(ctx->map, ctx->line) : ft_strcat("", ctx->line);
    if (!tmp) return 0;
    free(ctx->map);
    ctx->map = tmp;
    return 1;
}


