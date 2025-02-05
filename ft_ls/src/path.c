#include <sys/stat.h> //  struct stat
#include <pwd.h>      //  getpwuid()
#include <grp.h>      //  getgrgid()
#include <time.h>     //  ctime()
#include "utils.h"



t_file_info *create_file_info(const char *name,const char *path)
{
    t_file_info *file;

    file = malloc(sizeof(t_file_info));
    if (!file)
        return NULL;
    file->name = ft_strdup(name);  
    if (!file->name)
    {
        free(file);
        return NULL;
    }
    file->path = ft_strdup(path);
    if (!file->path)
    {
        free(file->name);
        free(file);
        return NULL;
    }
    stat(path, &file->stats);
    return file;
}

void free_file_info(t_file_info *file)
{
    if (!file)
        return;
    free(file->name);
    free(file->path);
    file->name = NULL;
    file->path = NULL;
    free(file);
}