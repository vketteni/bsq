#include "bsq.h"

#include <stdio.h> 

int init_squares(int ***squares_ptr, BsqContext *ctx) {
    if (!(ctx->map_height > 0 && ctx->map_width > 0))
        return 0;
    *squares_ptr = (int **)calloc_2d_array(ctx->map_height, ctx->map_width, sizeof(int *));
    if (!(*squares_ptr))
        return 0;
    return 1;
}
int init_map(char ***map_ptr, BsqContext *ctx) {
    if (!(ctx->map_height > 0))
        return 0;
    *map_ptr = (char **)calloc(ctx->map_height, sizeof(char *));
    if (!(*map_ptr))
        return 0;
    return 1;
}

int mark_on_map(char **map, int **squares, BsqContext *ctx) {
    if (!map || !squares)
        return 0;
    if (ctx->bsq_x < ctx->bsq_size && ctx->bsq_y < ctx->bsq_size)
        return 0;

    int start_y = ctx->bsq_y - ctx->bsq_size;
    int end_y = ctx->bsq_y;
    int start_x = ctx->bsq_x - ctx->bsq_size;
    int end_x = ctx->bsq_x;

    for (int y = start_y; y < end_y; ++y) {
        for (int x = start_x; x < end_x; ++x)
            map[y][x] = ctx->full;
    }
    return 1;
}

int print_map(char **map, BsqContext *ctx) {
    for (int i = 0; i < ctx->map_height; ++i)
        fprintf(stdout, "%s", map[i]);
    return 1;
}
