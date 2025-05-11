#include "bsq.h"

void free_bsq(FILE *fp, char **map, int **squares, BsqContext *ctx) {
    if (fp && fp != stdin) {
        fclose(fp);
    }
    if (map) {
        free_2d_array((void **)map, ctx->map_height);
    }
    if (squares) {
        free_2d_array((void **)squares, ctx->map_height);
    }
}

