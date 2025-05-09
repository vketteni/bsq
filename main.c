#include <stdlib.h>

#include "bsq.h"
#include "input.h"
#include "dp.h"
#include "map.h"

/*
main.c
└── bsq(file_path)
    ├── open_input()
    ├── parse_header()
    ├── parse_body()
    │   └── fill map & dp table
    ├── find_largest_square()
    ├── mark_square_on_map()
    └── print_map()
*/

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
    ParsingContext  parsing_ctx = {0};
    ProcessingContext processing_ctx = {0};

    CHECK( parsing_ctx.fp = open_input(file_path) );
    CHECK( parse_header(&parsing_ctx) );
    CHECK( parse_body(&parsing_ctx) ); // produces valid map 
    CHECK( init_processing_context(&processing_ctx, &parsing_ctx) );
    CHECK( fill_dp_table_and_track_bsq(&processing_ctx) );
    CHECK( mark_bsq_on_map(&processing_ctx) );
    CHECK( print_map(&processing_ctx) );

    free_parsing_context(&parsing_ctx);
    free_processing_context(&processing_ctx);
    return 1;
    
    error:
        fprintf(stderr, "map error\n");
        free_parsing_context(&parsing_ctx);
        free_processing_context(&processing_ctx);
        return 0;
}

void free_parsing_context(ParsingContext *ctx) {
    if (ctx->fp && ctx->fp != stdin) {
        fclose(ctx->fp);
    }
    if (ctx->line) {
        free(ctx->line);
    }
}

void free_processing_context(ProcessingContext *ctx) {
    if (ctx->dp) {
        free_dp_matrix(ctx->dp);
    }

    if (ctx->map) {
        free(ctx->map);
    }
}
