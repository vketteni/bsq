#include <stdlib.h>

#include "bsq.h"

int main(int argc, char **argv) {
	if (argc == 1)
		bsq(NULL);
	else {
		for (int i = 1; i < argc; ++i)
			bsq(argv[i]);
	}
	return 0;
}

int bsq(const char *file_path) {
    BsqContext ctx = {0};    
    FILE *fp = NULL;
    char **map = NULL;

    CHECK( fp = open_input(file_path) );
    CHECK( parse_header(fp, &ctx) );
    CHECK( init_map(&map, &ctx) );
    CHECK( parse_body(fp, map, &ctx) );
    CHECK( find_bsq(map, &ctx) );
    CHECK( mark_on_map(map, &ctx) );
    CHECK( print_map(map, &ctx) );

    free_bsq(fp, map, &ctx);
    return 1;
    
    error:
        fprintf(stderr, "map error\n");
        free_bsq(fp, map, &ctx);
        return 0;
}

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

int parse_body(FILE *fp, char **map, BsqContext *ctx) {
    size_t line_cap = 0;
    int line_len = 0;
    for (int i = 0; i < ctx->map_height; ++i) {
        line_len = getline(&map[i], &line_cap, fp);
        if (line_len < 0) {
            return 0;
	}
	if (i == 0) {
            ctx->map_width = line_len - 1; // minus one because new line is excluded
	}
        if (!valid_line_format(map[i], ctx)) {
            return 0;
        }
    }
    return 1;
}

int valid_line_format(char *line, BsqContext *ctx) {
    int i = 0; 
    while (line[i] != '\n' && line[i] != '\0') {
        if (line[i] == ctx->empty || line[i] == ctx->obstacle) {
            ++i;
            continue;
        } 
        return 0;
    }
    return (i == ctx->map_width);
}

int find_bsq(char **map, BsqContext *ctx) {
    int squares[ctx->map_height][ctx->map_width];

    for (int i = 0; i < ctx->map_height; ++i) {
        for (int j = 0; j < ctx->map_width; ++j) {
            // Track Possible Square
            if (map[i][j] == ctx->obstacle) {
                squares[i][j] = 0;
            }
            else if (i != 0 && j != 0) { 
                int top = squares[i - 1][j];
                int left = squares[i][j - 1];
                int diag = squares[i - 1][j - 1];
                squares[i][j] = ft_min(top, ft_min(left, diag)) + 1;
            } else {
                squares[i][j] = 1;
            }
            // Set Biggest Square
            if (ctx->bsq_size < squares[i][j]) {
                ctx->bsq_size = squares[i][j];
                ctx->bsq_x = j + 1;
                ctx->bsq_y = i + 1;
            }
        }
    }
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

int mark_on_map(char **map, BsqContext *ctx) {
    if (!map || !ctx)
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

int ft_min(int a, int b) {
    if (a < b) return a;
    return b;
}

void free_bsq(FILE *fp, char **map, BsqContext *ctx) {
    if (fp && fp != stdin) {
        fclose(fp);
    }
    if (map) {
		for (int i = 0; i < ctx->map_height; ++i) {
			if (map[i]) {
				free(map[i]);
			}
		}
		free(map);
    }
}

