#include "utils.h"
#include <stdlib.h>

void	free_2d_array(void **arr_2d, size_t rows) {
	if (arr_2d) {
		for (size_t i = 0; i < rows; ++i) {
			if (arr_2d[i]) {
				free(arr_2d[i]);
			}
		}
		free(arr_2d);
	}
}

void	**calloc_2d_array(size_t rows, size_t collumns, size_t elem_size) {
	void **arr = calloc(rows, sizeof(void *));
	if (!arr) return NULL;
	for (size_t i = 0; i < rows; ++i) {
		arr[i] = calloc(collumns, elem_size);
		if (!(arr[i])) {
			free_2d_array(arr, rows);
			return NULL;
		}
	}
	return arr;
}

int ft_min(int a, int b) {
    if (a < b) return a;
    return b;
}
