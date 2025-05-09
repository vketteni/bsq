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
    for (size_t i = 0; i < ctx->rows; ++i) {
        ctx->line_len = getline(&ctx->map[i], &ctx->line_cap, ctx->fp)
        if (ctx->line_len < 0 || !valid_line_format(ctx, i))
            return 0;
    }
    return 1;
}

int valid_line_format(ParsingContext *ctx, size_t line_index) {
    if (line_index == 0) {
        ctx->cols = ctx->line_len - 1; // minus one because new line is excluded
    }
    char *line = ctx->map[line_index];
    size_t i = 0; 
    while (line[i] != '\n' || line[i] != '\0') {
        if (line[i] == ctx->symbols[EMPTY] || line[i] == ctx->symbols[OBSTACLE]) {
            ++i;
            continue;
        } 
        return 0;
    }
    return i == ctx->cols;
}

int append_line_to_map(ParsingContext *ctx) {
    char    *tmp;
    
    tmp = ctx->map ? ft_strcat(ctx->map, ctx->line) : ft_strcat("", ctx->line);
    if (!tmp) return 0;
    free(ctx->map);
    ctx->map = tmp;
    return 1;
}


