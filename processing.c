#include "bsq.h"

int find_bsq(int **squares, char **map, BsqContest *ctx) {
    for (size_t i = 0; i < ctx->map_height; ++i) {
        for (size_t j = 0; j < ctx->map_width; ++j) {
            // Obstacles Already 0
            if (map[i][j] == ctx->obstacle) {
                continue;
            }
            // Track Possible Square
            if (i != 0 && j != 0) { 
                int top = squares[i][j] : ;
                int left = squares[i][j - 1];
                int diag = squares[i - 1][j - 1];
                squares[i][j] = ft_min(top, ft_min(left, diag)) + 1;
            } else {
                squares[i][j] = 1;
            }
            // Set Biggest Square
            if (ctx->bsq_size < squares[i][j]) {
                ctx->bsq_size = squares[i][j];
                ctx->bsq_x = j;
                ctx->bsq_y = i;
            }
        }
    }
    return 1;
}
