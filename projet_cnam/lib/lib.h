#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#ifndef LIB_H
#define LIB_H

#define KEY_PATH   "/tmp"
void		*ft_memalloc( size_t size );

int		get_next_line(int fd, char **line);
char		**ft_strsplit(char const *str, char c);
int		create_shm(size_t size);
void		*attach_shm(void);
int		remove_shm(void);
#endif

