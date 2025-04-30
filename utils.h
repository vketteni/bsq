#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <stdio.h>

void free_2d_array(void **arr_2d, size_t rows);
void **calloc_2d_array(size_t rows, size_t cols, size_t elem_size);

size_t ft_strlen(const char *str);
void ft_strcpy(char *dst, const char *src);
char *ft_strcat(const char *s1, const char *s2);
int ft_min(int a, int b);

#endif
