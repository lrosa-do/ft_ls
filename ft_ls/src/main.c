#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "utils.h"
#include <sys/stat.h>
#include <dirent.h>




void print_vector(t_vector *vector)
{
    size_t i;

    i = 0;
    printf("\nArquivos no vetor:\n");
    while (i < vector->size)
    {
        printf("%s\n", vector->data[i]->name);
        i++;
    }
    printf("Total: %zu arquivos\n", vector->size);
}


int test_vector()
{
    t_vector vector;
    t_file_info *file;

  
    if (!vector_init(&vector, 2))
    {
        printf("Erro ao inicializar vetor\n");
        return 1;
    }

    file = create_file_info("banana.txt");
    vector_push(&vector, file);

    file = create_file_info("abacaxi.txt");
    vector_push(&vector, file);

    file = create_file_info("morango.txt");
    vector_push(&vector, file);


    printf("Antes de ordenar:");
    print_vector(&vector);

    // Ordenar em ordem crescente (a-z)
    vector_sort(&vector, 1);
    printf("\nDepois de ordenar (a-z):");
    print_vector(&vector);

    // Ordenar em ordem decrescente (z-a)
    vector_sort(&vector, 0);
    printf("\nDepois de ordenar (z-a):");
    print_vector(&vector);



    vector_free(&vector);

    return 0;
}

void test_strlen()
{
    printf("Testing ft_strlen:\n");
    printf("Length of 'Hello': %zu\n", ft_strlen("Hello"));
    printf("Length of '42': %zu\n", ft_strlen("42"));
    printf("Length of '': %zu\n\n", ft_strlen(""));
}

void test_strdup()
{
    printf("Testing ft_strdup:\n");
    char *dup = ft_strdup("Hello World");
    printf("Duplicate: %s\n\n", dup);
    free(dup);
}

void test_strcmp()
{
    printf("Testing ft_strcmp:\n");
    printf("Compare 'abc' vs 'abc': %d\n", ft_strcmp("abc", "abc"));
    printf("Compare 'abc' vs 'abd': %d\n", ft_strcmp("abc", "abd"));
    printf("Compare 'abd' vs 'abc': %d\n\n", ft_strcmp("abd", "abc"));
}

void test_itoa()
{

    char buffer[128];
    printf("Testing ft_itoa:\n");

    ft_itoa(42, buffer);
    printf("Number 42: %s\n", buffer);

    ft_itoa(-123, buffer);
    printf("Number -123: %s\n\n", buffer);
}


int main()
{
    test_strlen();
    test_strdup();
    test_strcmp();
    test_itoa();
    test_vector();
    

    return 0;
}
