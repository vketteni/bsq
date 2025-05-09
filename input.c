#include "input.h"
#include "bsq.h"
#include "utils.h"
#include <stdlib.h>
#include <stdbool.h>

FILE *open_input(const char *file_path) {
	return file_path ? fopen(file_path, "r") : stdin;
}

int parse_header(FILE *fp, BsqContext *ctx) {
    char end;
    int	result;
   
    result = fscanf(
        fp,
        "%d%c%c%c%c",
        &ctx->map_height,
        &ctx->empty,
        &ctx->obstacle,
        &ctx->full,
        &end
    );
    if (result != 5 || end != '\n' || ctx->map_height <= 0) {
        return 0;
    }
    return 1;
}

int parse_body(FILE *fp, char **bsq_map, BsqContext *ctx) {
    int line_cap = 0;
    int line_len = 0;
    for (int i = 0; i < ctx->map_height; ++i) {
        line_len = getline(&bsq_map[i], &line_cap, fp)
        if (line_len < 0) {
            return 0;
	}
	if (i == 0) {
            ctx->map_width = line_len - 1; // minus one because new line is excluded
	}
        if (!valid_format(map[i], ctx)) {
            return 0;
        }
    }
    return 1;
u

int valid_line_format(char *line, BsqContext *ctx) {
    int i = 0; 
    while (line[i] != '\n' && line[i] != '\0') {
        if (line[i] == ctx->empty || line[i] == ctx->obstacle) {
            ++i;
            continue;
        } 
        return 0;
    }
    return i == ctx->width_map;
}

int append_line_to_map(ParsingContext *ctx) {
    char    *tmp;
    
    tmp = ctx->map ? ft_strcat(ctx->map, ctx->line) : ft_strcat("", ctx->line);
    if (!tmp) return 0;
    free(ctx->map);
    ctx->map = tmp;
    return 1;
}


