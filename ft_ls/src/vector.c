#include <sys/stat.h> //  struct stat
#include <pwd.h>      //  getpwuid()
#include <grp.h>      //  getgrgid()
#include <time.h>     //  ctime()
#include "utils.h"



int vector_init(t_vector *vector, size_t capacity)
{
    vector->size = 0;
    vector->capacity = capacity;
    vector->data = malloc(capacity * sizeof(t_file_info *));
    if (!vector->data)
        return 0;
    return 1;
}

int _resize_vector(t_vector *vector, size_t new_capacity)
{
    t_file_info **new_data = malloc(new_capacity * sizeof(t_file_info *));
    if (!new_data)
        return 0;

    for (size_t i = 0; i < vector->size; i++)
        new_data[i] = vector->data[i];

    free(vector->data);
    vector->data = new_data;
    vector->capacity = new_capacity;

    return 1;
}

int vector_push(t_vector *vector, t_file_info *file_info)
{
    if (vector->size == vector->capacity)
    {
        size_t new_capacity = vector->capacity * 2;
        if (!_resize_vector(vector, new_capacity))
            return 0;
    }
    vector->data[vector->size++] = file_info;
    return 1;
}

void vector_free(t_vector *vector)
{
    if (!vector)
        return;
    if (!vector->data)
        return;
    for (size_t i = 0; i < vector->size; i++)
    {
        if (vector->data[i])
            free_file_info(vector->data[i]);
    }

    free(vector->data);
    vector->data = NULL;
    vector->size = 0;
    vector->capacity = 0;
}

#ifdef MERGE_ZORTED




// int compare_files(t_file_info *file1, t_file_info *file2, t_options *opts)
// {
    
//     //   `-t` ordenar por data de modificação
//     if (opts->t)
//     {
//         if (file1->stats.st_mtime > file2->stats.st_mtime)
//             return -1; // Ficheiro mais recente primeiro
//         if (file1->stats.st_mtime < file2->stats.st_mtime)
//             return 1;
//     }


//    //  por nome (padrão ou desempate para -t)
//     int cmp = ft_strcmp(file1->name, file2->name);
//     return opts->r ? -cmp : cmp;
// }



int compare_files(t_file_info *a, t_file_info *b, t_options *opts)
{
    // if (ft_strcmp(a->name, ".") == 0) return -1;
    // if (ft_strcmp(b->name, ".") == 0) return 1;
    // if (ft_strcmp(a->name, "..") == 0) return -1;
    // if (ft_strcmp(b->name, "..") == 0) return 1;


    if (opts->t)
    {
    
        if (a->stats.st_mtime != b->stats.st_mtime)
        {
            return (opts->r ? (a->stats.st_mtime > b->stats.st_mtime ? 1 : -1)
                            : (a->stats.st_mtime > b->stats.st_mtime ? -1 : 1));
        }

        // Se as datas forem iguais, ordenar por nome
    }

    // Comparação por nome ..... >>>ordenação ASCII  `LC_ALL=C`
    int cmp = ft_strcasecmp(a->name, b->name);
    return (opts->r ? -cmp : cmp);
}


void merge(t_file_info **data, t_file_info **temp, int left, int mid, int right, t_options *opts)
{
    int i = left, j = mid + 1, k = left;

    while (i <= mid && j <= right)
    {
        if (compare_files(data[i], data[j], opts) <= 0)
            temp[k++] = data[i++];
        else
            temp[k++] = data[j++];
    }

    while (i <= mid)
        temp[k++] = data[i++];

    while (j <= right)
        temp[k++] = data[j++];

    for (i = left; i <= right; i++)
        data[i] = temp[i];
}


void merge_sort_recursive(t_file_info **data, t_file_info **temp, int left, int right, t_options *opts)
{
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    merge_sort_recursive(data, temp, left, mid, opts);
    merge_sort_recursive(data, temp, mid + 1, right, opts);
    merge(data, temp, left, mid, right, opts);
}


void vector_sort(t_vector *vector, t_options *opts)
{
    if (!vector || vector->size < 2)
        return;

    t_file_info **temp = malloc(vector->size * sizeof(t_file_info *));
    if (!temp)
        return; 

    merge_sort_recursive(vector->data, temp, 0, vector->size - 1, opts);
    free(temp);
}

#else

void swap_elements(t_file_info **a, t_file_info **b)
{
    t_file_info *temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

int partition(t_vector *vector, int low, int high, int ascend)
{
    t_file_info *pivot;
    int i;
    int j;

    pivot = vector->data[high];
    i = low - 1;

    for (j = low; j < high; j++)
    {
        if (ascend)
        {
            if (ft_strcmp(vector->data[j]->name, pivot->name) <= 0)
            {
                i++;
                swap_elements(&vector->data[i], &vector->data[j]);
            }
        }
        else
        {
            if (ft_strcmp(vector->data[j]->name, pivot->name) >= 0)
            {
                i++;
                swap_elements(&vector->data[i], &vector->data[j]);
            }
        }
    }
    swap_elements(&vector->data[i + 1], &vector->data[high]);
    return (i + 1);
}

void quicksort(t_vector *vector, int low, int high, int ascend)
{
    int pi;

    if (low < high)
    {
        pi = partition(vector, low, high, ascend);
        quicksort(vector, low, pi - 1, ascend);
        quicksort(vector, pi + 1, high, ascend);
    }
}

int vector_sort(t_vector *vector, int ascend)
{
    if (!vector || !vector->data || vector->size < 2)
        return (1);
    quicksort(vector, 0, vector->size - 1, ascend);
    return (1);
}

#endif

