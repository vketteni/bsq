#include "dp.h"
#include "bsq.h"
#include "utils.h"

DPMatrix *create_dp_matrix(int rows, int cols) {
    DPMatrix *dp = (DPMatrix *)calloc(1, sizeof(DPMatrix));
    
    dp->table = (size_t **)calloc_2d_array(rows, cols, sizeof(size_t));
    dp->rows = rows;
    dp->cols = cols;
    return dp; 
}

void free_dp_matrix(DPMatrix* dp) {
    free_2d_array((void **)dp->table, dp->rows);
    free(dp);
}

int init_processing_context(ProcessingContext *proc, ParsingContext *parse) {
    proc->rows = parse->rows;
    proc->cols = parse->cols;
    proc->map = parse->map;
    parse->map = NULL;

    for (int i = 0; i < 3; ++i) {
        proc->symbols[i] = parse->symbols[i];
    }   

    proc->dp = create_dp_matrix(proc->rows + EXTRA_BORDER, proc->cols + EXTRA_BORDER);
    if (!proc->dp)
        return 0;

    proc->bsq.size = 0;
    proc->bsq.x = 0;
    proc->bsq.y = 0;
    return 1;
}

int fill_dp_table_and_track_bsq(ProcessingContext *ctx) {
    char *map = ctx->map;
    DPMatrix *dp = ctx->dp;
    if (!dp || !map)
        return 0;
    Square *bsq = &ctx->bsq;
    for (size_t i = 0 + EXTRA_BORDER; i < dp->rows; ++i) {
        for (size_t j = 0 + EXTRA_BORDER; j < dp->cols; ++j) {
            size_t map_index = (i - EXTRA_BORDER)*(ctx->cols + NEW_LINE) + (j - EXTRA_BORDER);
            
            if (map[map_index] == ctx->symbols[OBSTACLE]) {
                continue;
            }
            // Fill Table
            int top = dp->table[i - 1][j];
            int left = dp->table[i][j - 1];
            int diag = dp->table[i - 1][j - 1];
            dp->table[i][j] = ft_min(top, ft_min(left, diag)) + 1;
            // Track Bsq
            if (bsq->size < dp->table[i][j]) {
                bsq->size = dp->table[i][j];
                bsq->x = j;
                bsq->y = i;
            }
        }
    }
    return 1;
}

