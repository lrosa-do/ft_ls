#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

size_t ft_strlen(const char *s)
{
    size_t len = 0;
    if (!s)
        return 0;
    while (s[len])
        len++;
    return len;
}

char *ft_strcpy(char *dest, const char *src)
{
    if (!dest || !src)
        return NULL;
    size_t i = 0;
    while (src[i])
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}

char *ft_strdup(const char *s)
{
    if (!s)
        return NULL;
    size_t len = ft_strlen(s);
    char *copy = malloc(len + 1);
    if (!copy)
        return NULL;
    return ft_strcpy(copy, s);
}

int ft_strcmp(const char *s1, const char *s2)
{
    if (!s1 || !s2)
        return (s1 == s2) ? 0 : (s1 ? 1 : -1);
    while (*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return (unsigned char)(*s1) - (unsigned char)(*s2);
}

char *ft_strdup_peliculas(const char *s)
{
    if (!s)
        return NULL;

    size_t len = ft_strlen(s);
    int has_space = 0;
   size_t i;

 
    for (i = 0; i < len; i++)
    {
        if (s[i] == ' ')
        {
            has_space = 1;
            break;
        }
    }


    char *copy = malloc(len + (has_space ? 3 : 1));
    if (!copy)
        return NULL;


    if (has_space)
    {
        copy[0] = '\'';
        ft_strcpy(copy + 1, s);
        copy[len + 1] = '\'';
        copy[len + 2] = '\0';
    }
    else
    {
        ft_strcpy(copy, s);
    }

    return copy;
}

int ft_lower(int c)
{
    if (c >= 'A' && c <= 'Z')
        return c + ('a' - 'A');
    return c;
}



int ft_strcasecmp(const char *s1, const char *s2)
{
    unsigned char c1, c2;

    while (*s1 || *s2)
    {
        c1 = ft_lower((unsigned char)*s1);
        c2 = ft_lower((unsigned char)*s2);

        if (c1 != c2)
            return c1 - c2;

        s1++;
        s2++;
    }
    return 0;
}


char *ft_strcat(char *dest, const char *src)
{
    if (!dest || !src)
        return NULL;
    char *ptr = dest + ft_strlen(dest);
    while (*src)
        *ptr++ = *src++;
    *ptr = '\0';
    return dest;
}

int ft_itoa(int n, char *buffer)
{
    int len = (n <= 0) ? 1 : 0, temp = n;

    int buffer_size = ft_strlen(buffer);

    while (temp)
    {
        temp /= 10;
        len++;
    }

    if (buffer_size <= len)
    {
        return 0;
    }

    buffer[len] = '\0';
    if (n == 0)
        buffer[0] = '0';
    if (n < 0)
        buffer[0] = '-';

    while (n)
    {
        buffer[--len] = '0' + ((n % 10) * (n < 0 ? -1 : 1));
        n /= 10;
    }

    return 1;
}

void *ft_memset(void *s, int c, size_t n)
{
    if (!s)
        return NULL;
    unsigned char *ptr = s;
    while (n--)
        *ptr++ = (unsigned char)c;
    return s;
}

void *ft_memcpy(void *dest, const void *src, size_t n)
{
    if (!dest || !src)
        return NULL;
    unsigned char *d = dest;
    const unsigned char *s = src;
    while (n--)
        *d++ = *s++;
    return dest;
}

void ft_itoa_buffer(long num, char *buffer)
{
    int i = 0;
    int is_negative = (num < 0);

    if (is_negative)
        num = -num;

    do
    {
        buffer[i++] = (num % 10) + '0';
        num /= 10;
    } while (num > 0);

    if (is_negative)
        buffer[i++] = '-';

    buffer[i] = '\0';

    int start = 0, end = i - 1;
    while (start < end)
    {
        char temp = buffer[start];
        buffer[start] = buffer[end];
        buffer[end] = temp;
        start++;
        end--;
    }
}


char ft_is_space(const char *s)
{
    if (!s)
        return 0;

    size_t len = ft_strlen(s);
    char has_space = 0;
    size_t i;

 
    for (i = 0; i < len; i++)
    {
        if (s[i] == ' ')
        {
            has_space = 1;
            break;
        }
    }

    return has_space;
}

void ft_print_str(const char *str,char is_name)
{

    if (!str)
        return;
    
    if ( is_name==1)
    {

        if (ft_is_space(str) ==1)
        {
            write(1, "'", 1);
            write(1, str, ft_strlen(str));
            write(1, "'", 1);
            
        } else 
            write(1, str, ft_strlen(str));
    }
    else
        write(1, str, ft_strlen(str));
}

void ft_error_str(const char *str, const char *err, char nl)
{
    write(1, str, ft_strlen(str));
    write(1, err, ft_strlen(err));
    if (nl == 1)
    {
        write(1, "\n", 1);
    }
}



char *ft_strncpy(char *dst, const char *src, size_t len)
{
    char *ptrdst;

    ptrdst = dst;
    while (*src && len)
    {
        *(ptrdst++) = *(src++);
        len--;
    }
    while (len)
    {
        *(ptrdst++) = 0;
        len--;
    }
    return (dst);
}

void ft_join_path(char *buffer, size_t size, const char *path, const char *name)
{
    size_t path_len = ft_strlen(path);
    size_t name_len = ft_strlen(name);

    if (path_len + name_len + 2 > size) // +2 para '/' e '\0'
        return;

    ft_strcpy(buffer, path);

    if (path[path_len - 1] != '/')
    {
        buffer[path_len] = '/';
        path_len++;
    }

    ft_strcpy(buffer + path_len, name);
}

char *ft_strnew(size_t size)
{
    char *str;
    char *ptrstr;

    if (!(str = (char *)malloc(sizeof(char) * size + 1)))
        return (NULL);
    ptrstr = str;
    while (size + 1)
    {
        *ptrstr = 0;
        ptrstr++;
        size--;
    }
    return (str);

}

char *ft_strjoin(const char *s1, const char *s2)
{
    char *join;

    if (!s1 || !s2)
        return (NULL);
    if (!(join = ft_strnew(ft_strlen(s1) + ft_strlen(s2) + 1)))
        return (NULL);
    return (ft_strcat(ft_strcat(join, s1), s2));
}

char *ft_strsub(const char *s, unsigned int start, size_t len)
{
    char *sub;

    if (!s)
        return (NULL);
    if (!(sub = ft_strnew(len)))
        return (NULL);
    while (start--)
        s++;
    return (ft_strncpy(sub, s, len));
}
