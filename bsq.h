#ifndef BSQ_H
#define BSQ_H

#include <stdio.h>  // Needed for FILE

// Constants
#define EMPTY 0
#define FULL 1
#define OBSTACLE 2
#define EXTRA_BORDER 1
#define NEW_LINE 1

// Shared types
typedef struct DPMatrix {
    size_t **table;
    size_t rows;
    size_t cols;
} DPMatrix;

typedef struct BsqContext {
    char full;
    char empty;
    char obstacle;
    int width_map;
    int height_map;
} BsqContext;


typedef struct Square {
    size_t x;
    size_t y;
    size_t size;
} Square;

typedef struct ParsingContext {
    FILE *fp;
    char *line;
    ssize_t line_len;
    size_t line_cap;
    size_t rows;
    size_t cols;
    char **map;
    char symbols[3]; // empty, full, obstacle
} ParsingContext;

typedef struct ProcessingContext {
    size_t rows;
    size_t cols;
    char *map;
    DPMatrix *dp;
    Square bsq;
    char symbols[3]; // copy from parsing
} ProcessingContext;

// Main bsq function
int bsq(const char *file_path);
void free_parsing_context(ParsingContext *ctx);
void free_processing_context(ProcessingContext *ctx);

// Error checking macro
#define CHECK(x) do { if (!(x)) goto error; } while (0)

#endif // BSQ_H
