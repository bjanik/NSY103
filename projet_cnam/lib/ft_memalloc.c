#include "lib.h"

void    *ft_memalloc(size_t size)
{
        void    *ptr;

        if ((ptr = malloc(size)) == NULL)
                return (NULL);
        memset(ptr, 0, size);
        return (ptr);
}
