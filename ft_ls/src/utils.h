#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>
#include <stdlib.h>

#define MERGE_ZORTED 1

typedef struct s_file_info
{
    char *name;
    char *path;
    struct stat stats;
} t_file_info;

typedef struct s_vector
{
    size_t size;
    size_t capacity;
    t_file_info **data;
} t_vector;

typedef struct s_options
{
    int l; // lista detalhada
    int R; // recursivo
    int a; //   ocultos
    int r; //  reversa
    int t; // ordem por tempo de modificação
} t_options;

size_t ft_strlen(const char *s);
char *ft_strcpy(char *dest, const char *src);
char *ft_strdup(const char *s);
int ft_strcmp(const char *s1, const char *s2);
char *ft_strcat(char *dest, const char *src);
int ft_itoa(int n, char *buffer);
void *ft_memset(void *s, int c, size_t n);
void *ft_memcpy(void *dest, const void *src, size_t n);
void ft_itoa_buffer(long num, char *buffer);
void ft_print_str(const char *str);
void ft_join_path(char *buffer, size_t size, const char *path, const char *name);
void ft_error_str(const char *str, const char *err, char nl);

char *ft_strnew(size_t size);
char *ft_strjoin(const char *s1, const char *s2);
char *ft_strsub(const char *s, unsigned int start, size_t len);
char *ft_strncpy(const char *dst, const char *src, size_t len);
char *ft_strcpy(char *dst, const char *src);
char *ft_get_time(time_t tv_sec);

t_file_info *create_file_info(const char *name, const char *path);
void free_file_info(t_file_info *file_info);

int vector_init(t_vector *vector, size_t capacity);
void vector_free(t_vector *vector);
int vector_push(t_vector *vector, t_file_info *file_info);
void vector_sort(t_vector *vector, t_options *opts);

void print_simple_list(t_vector *vector);
void print_detailed_list(t_vector *vector);

#endif
