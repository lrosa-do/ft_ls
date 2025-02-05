#include <sys/stat.h> //  struct stat
#include <pwd.h>      //  getpwuid()
#include <grp.h>      //  getgrgid()
#include <time.h>     //  ctime()
#include <dirent.h>   //  opendir, readdir, closedir
#include <unistd.h>
#include <stdio.h>
#include "utils.h"


void print_filename_colored(t_file_info *file)
{
    if (S_ISDIR(file->stats.st_mode))
        ft_print_str("\033[1;34;44m"); //  Azul com fundo azul
    else if (S_ISLNK(file->stats.st_mode))
        ft_print_str("\033[1;36m"); //  Ciano para links simbólicos
    else
        ft_print_str("\033[1;32m"); //  Verde para ficheiros normais

    ft_print_str(file->name);
    ft_print_str("\033[0m");
}

void print_file_permissions(long long mode)
{
    write(1, (S_ISDIR(mode)) ? "d" : "-", 1);
    write(1, (mode & S_IRUSR) ? "r" : "-", 1);
    write(1, (mode & S_IWUSR) ? "w" : "-", 1);
    write(1, (mode & S_IXUSR) ? "x" : "-", 1);
    write(1, (mode & S_IRGRP) ? "r" : "-", 1);
    write(1, (mode & S_IWGRP) ? "w" : "-", 1);
    write(1, (mode & S_IXGRP) ? "x" : "-", 1);
    write(1, (mode & S_IROTH) ? "r" : "-", 1);
    write(1, (mode & S_IWOTH) ? "w" : "-", 1);
    write(1, (mode & S_IXOTH) ? "x" : "-", 1);
}

void print_simple_list(t_vector *vector)
{
    for (size_t i = 0; i < vector->size; i++)
    {
        print_filename_colored(vector->data[i]);
        write(1, "\n", 1);
    }
}

void print_total_blocks(t_vector *vector)
{
    long total = 1;
    char str[512];

    for (size_t i = 0; i < vector->size; i++)
        total += vector->data[i]->stats.st_blocks;

    //    // Divisão por 2 porque `st_blocks` usa blocos de 512 bytes

    total /= 2;

    ft_itoa_buffer(total, str);

    ft_print_str("total ");
    ft_print_str(str);
    ft_print_str("\n");
}

char *ft_get_time(time_t tv_sec)
{
    char *time_fmt;
    char *tmp;
    char *tmp2;
    time_t today;

    (void)time(&today);
    if (today - tv_sec > 14515200)
    {
        tmp = ctime(&tv_sec);
        tmp2 = ft_strsub(tmp, 4, 7);
        tmp = ft_strsub(tmp, 19, 5);
        time_fmt = ft_strjoin(tmp2, tmp);
        free(tmp);
        free(tmp2);
    }
    else
        time_fmt = ft_strsub(ctime(&tv_sec), 4, 12);
    return time_fmt;
}

void calculate_column_widths(t_vector *vector, size_t *link_width,
                             size_t *user_width, size_t *group_width, size_t *size_width)
{
    struct passwd *pw;
    struct group *gr;
    char buffer[32];
    size_t i;

    *link_width = 0;
    *user_width = 0;
    *group_width = 0;
    *size_width = 0;

    for (i = 0; i < vector->size; i++)
    {
        t_file_info *file = vector->data[i];

    
        ft_itoa_buffer(file->stats.st_nlink, buffer);
        if (*link_width < ft_strlen(buffer))
            *link_width = ft_strlen(buffer);

        pw = getpwuid(file->stats.st_uid);
        if (pw && *user_width < ft_strlen(pw->pw_name))
            *user_width = ft_strlen(pw->pw_name);


        gr = getgrgid(file->stats.st_gid);
        if (gr && *group_width < ft_strlen(gr->gr_name))
            *group_width = ft_strlen(gr->gr_name);


        ft_itoa_buffer(file->stats.st_size, buffer);
        if (*size_width < ft_strlen(buffer))
            *size_width = ft_strlen(buffer);
    }
}


void print_detailed_list(t_vector *vector)
{
    struct passwd *pw;
    struct group *gr;
    char buffer[1024];
    char link_target[4096];
    ssize_t link_len;
    size_t link_width, user_width, group_width, size_width;

    calculate_column_widths(vector, &link_width, &user_width, &group_width, &size_width);

    print_total_blocks(vector);

    for (size_t i = 0; i < vector->size; i++)
    {
        t_file_info *file = vector->data[i];

        //  Permissões
        print_file_permissions(file->stats.st_mode);
        write(1, " ", 1);

        //  Numero de links
        ft_itoa_buffer(file->stats.st_nlink, buffer);
        for (size_t j = ft_strlen(buffer); j < link_width; j++)
            write(1, " ", 1);
        ft_print_str(buffer);
        write(1, " ", 1);

        // Dono do ficheiro
        pw = getpwuid(file->stats.st_uid);
        if (pw)
        {
            ft_print_str(pw->pw_name);
            for (size_t j = ft_strlen(pw->pw_name); j < user_width + 1; j++)
                write(1, " ", 1);
        }

        // Grupo do ficheiro
        gr = getgrgid(file->stats.st_gid);
        if (gr)
        {
            ft_print_str(gr->gr_name);
            for (size_t j = ft_strlen(gr->gr_name); j < group_width + 1; j++)
                write(1, " ", 1);
        }

        // Tamanho do ficheiro
        ft_itoa_buffer(file->stats.st_size, buffer);
        for (size_t j = ft_strlen(buffer); j < size_width; j++)
            write(1, " ", 1);
        ft_print_str(buffer);
        write(1, " ", 1);

        // Data
        char *dt = ft_get_time(file->stats.st_mtime);
        write(1, dt, ft_strlen(dt));
        free(dt);
        write(1, " ", 1);

        //  Nome do ficheiro
        print_filename_colored(file);

        //   link simbólico
        if (S_ISLNK(file->stats.st_mode))
        {
            link_len = readlink(file->path, link_target, sizeof(link_target) - 1);
            if (link_len != -1)
            {
                link_target[link_len] = '\0';
                ft_print_str(" -> ");
                ft_print_str("\033[1;32m"); 
                ft_print_str(link_target);
                ft_print_str("\033[0m");
            }
        }
        write(1, "\n", 1);
    }
}
