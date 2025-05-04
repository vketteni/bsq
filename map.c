#include "map.h"
#include "bsq.h"
#include <stdio.h> 

int mark_bsq_on_map(ProcessingContext *ctx) {
    char *map = ctx->map;
    DPMatrix *dp = ctx->dp;
    if (!dp || !map)
        return 0;
    Square *bsq = &ctx->bsq;
    if (bsq->x >= bsq->size && bsq->y >= bsq->size) {
        size_t start_y = bsq->y - bsq->size;
        size_t end_y = bsq->y;
        size_t start_x = bsq->x - bsq->size;
        size_t end_x = bsq->x;
    
        for (size_t y = start_y; y < end_y; ++y) {
            for (size_t x = start_x; x < end_x; ++x) {
                size_t map_index = y * (ctx->cols + NEW_LINE) + x;
                map[map_index] = ctx->symbols[FULL];
            }
        }
    }

}

int print_map(ProcessingContext *ctx) {
    fprintf(stdout, "%s", ctx->map);
    return 1;
}
