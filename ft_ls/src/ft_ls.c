#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

int read_directory(const char *path, t_vector *vector, t_options *opts)
{
    DIR *dir = opendir(path);
    if (!dir)
    {
        perror("ft_ls");
        return 0;
    }

    struct dirent *entry;

    while ((entry = readdir(dir)))
    {
        if (!opts->a && entry->d_name[0] == '.')
        {
            continue; // Saltamos as files ocultos se -a não estiver presente
        }

        char full_path[4096];
        ft_join_path(full_path, sizeof(full_path), path, entry->d_name);

        struct stat file_stat;
        if (lstat(full_path, &file_stat) == -1)
            continue;

        t_file_info *file_info = create_file_info(entry->d_name, full_path);
        if (!file_info)
            continue;

        file_info->stats = file_stat;
        vector_push(vector, file_info);
    }

    closedir(dir);
    return 1;
}


// void print_directory_name(const char *dir_name)
// {
//     if (dir_name[0] != '/' && dir_name[0] != '.')
//     {
//         ft_print_str("./");
//     }
//     write(1, ":", 1);
//     ft_print_str(dir_name);
//     write(1, "\n", 1);
// }

void print_directory_name(const char *dir_name)
{
    if (dir_name[0] == '/')
        ft_print_str(dir_name);
    else
    {
     //   ft_print_str("./");
        ft_print_str(dir_name);
    }
    write(1, ":\n", 2);
}

void process_directory(const char *path, t_options *opts,int start,int count)
{
    t_vector vector;
    if (!vector_init(&vector, 100))
        return;

    if (!read_directory(path, &vector, opts))
    {
        vector_free(&vector);
        return;
    }
    if (vector.size > 0)  
        vector_sort(&vector, opts);
   
    if (ft_strcmp(path, ".") != 0)
    {
        print_directory_name(path);
    }
    if (start == 0 && count == 0)
    {

    }

    if (opts->l)
        print_detailed_list(&vector);
    else
        print_simple_list(&vector);

    if (opts->R)
    {
       
        for (size_t i = 0; i < vector.size; i++)
        {
            if (S_ISDIR(vector.data[i]->stats.st_mode) &&
                ft_strcmp(vector.data[i]->name, ".") != 0 &&
                ft_strcmp(vector.data[i]->name, "..") != 0)
            {
                write(1, "\n", 1);
                process_directory(vector.data[i]->path, opts,0,count);
            }
        }
    }

    vector_free(&vector);
}

int main(int argc, char **argv)
{
    t_options opts = {0};
    int i = 1;
    char with_r=0;
    while (i < argc && argv[i][0] == '-')
    {
        char *opt = argv[i] + 1;
        while (*opt)
        {
            if (*opt == 'l')
                opts.l = 1;
            else if (*opt == 'R')
            {
                opts.R = 1;
                with_r=1;
            }
            else if (*opt == 'a')
                opts.a = 1;
            else if (*opt == 'r')
                opts.r = 1;
            else if (*opt == 't')
                opts.t = 1;
            else
            {
                ft_error_str("ft_ls: invalid option -- ", opt, 1);
                return 1;
            }
            opt++;
        }
        i++;
    }

    if (i == argc)
    {
        if (with_r == 1)
        {
            write(1, ".\n", 2);
            write(1, "..\n", 3);
            with_r = 0;
        }
        process_directory(".", &opts, 1, i);
    }
    else
    {
        int first = 1;
        while (i < argc)
        {
            struct stat st;
            
            if (lstat(argv[i], &st) == -1)
            {
                ft_error_str("ft_ls: cannot access '", argv[i], 0);
                ft_print_str("': No such file or directory\n");
                //if (first) return 1;
                i++;
                continue;
            }
            
            if (!first)
                write(1, "\n", 1);
                
            process_directory(argv[i], &opts, 1, i);
            first = 0;
            i++;
        }
    }
   
    // if (i == argc)
    // {
    //     if (with_r==1)
    //     {
    //         write(1, ".\n", 2);
    //         write(1, "..\n", 3);
    //         with_r =  0;
    //     }
    //     process_directory(".", &opts,1,i);
    // }
    // else
    // {
    //     while (i < argc)
    //     {
    //         process_directory(argv[i], &opts,1,i);
    //         i++;
    //     }
    // }

    return 0;
}
