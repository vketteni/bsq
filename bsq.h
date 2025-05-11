#ifndef BSQ_H
#define BSQ_H

#include <stdlib.h>
#include <stdio.h>

typedef struct BsqContext {
    char full;
    char empty;
    char obstacle;
    int map_width;
    int map_height;
    int bsq_x; // Lower left corner
    int bsq_y; // Lower left corner
    int bsq_size; // Lower left corner
} BsqContext;

// Would be Interface 
int bsq(const char *file_path);

// Input
FILE *open_input(const char *file_path);
int parse_header(FILE *fp, BsqContext *ctx);
int valid_line_format(char *line, BsqContext *ctx);
int parse_body(FILE *fp, char **map, BsqContext *ctx);
// Map
int init_map(char ***map_ptr, BsqContext *ctx);
int init_squares(int ***squares_ptr, BsqContext *ctx);
int find_bsq(char **map, int **squares, BsqContext *ctx);
int mark_on_map(char **map, int **squares, BsqContext *ctx);
int print_map(char **map, BsqContext *ctx);
// Exit
void free_bsq(FILE *fp, char **map, int **squares, BsqContext *ctx);
// Utils
void **calloc_2d_array(size_t rows, size_t collumns, size_t elem_size);
void free_2d_array(void **arr_2d, size_t rows);
int ft_min(int a, int b);

// Error checking macro
#define CHECK(x) do { if (!(x)) goto error ; } while (0)

#endif // BSQ_H
