#ifndef MAP_H
#define MAP_H

// Forward declaration: we don't need full definition here
typedef struct ProcessingContext ProcessingContext;

int mark_bsq_on_map(ProcessingContext *ctx);
int print_map(ProcessingContext *ctx);

#endif // MAP_H

