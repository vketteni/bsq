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

size_t	ft_strlen(const char *str) {
	size_t i = 0;
	while (str[i]) {
		i++;
	}
	return i;
}

void	ft_strcpy(char *dest, const char *src) {
	while (*src) {
		*dest++ = *src++;
	}
	*dest = '\0';
}

char	*ft_strcat(const char *s1, const char *s2) {
	if (!s1 || !s2) return NULL;
	size_t	len1 = ft_strlen(s1);	
	size_t	len2 = ft_strlen(s2);
	char	*result = (char *)malloc(len1 + len2 + 1);
	if (!result) return NULL;

	ft_strcpy(result, s1);
	ft_strcpy(result + len1, s2);

	return result;
}

int ft_min(int a, int b) {
    if (a < b) return a;
    return b;
}
