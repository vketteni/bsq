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
    FILE *fp;
    char **map;
    int **squares;

    CHECK( fp = open_input(file_path) );
    CHECK( parse_header(fp, &ctx) );
    CHECK( init_map(&map, &ctx) );
    CHECK( parse_body(fp, map, &ctx) );
    CHECK( init_squares(&squares, &ctx) );
    CHECK( find_bsq(map, squares, &ctx) );
    CHECK( mark_on_map(map, squares, &ctx) );
    CHECK( print_map(map, &ctx) );

    free_bsq(fp, map, squares, &ctx);
    return 1;
    
    error:
        fprintf(stderr, "map error\n");
        free_bsq(fp, map, squares, &ctx);
        return 0;
}

