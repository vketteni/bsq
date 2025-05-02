#ifndef DP_H
#define DP_H

typedef struct ParsingContext ParsingContext;
typedef struct ProcessingContext ProcessingContext;
typedef struct DPMatrix DPMatrix;

DPMatrix *create_dp_matrix(int rows, int cols);
void free_dp_matrix(DPMatrix* dp);
int init_processing_context(ProcessingContext *proc, ParsingContext *parse);
int fill_dp_table_and_track_bsq(ProcessingContext *ctx);

#endif
