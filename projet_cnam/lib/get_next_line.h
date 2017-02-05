#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#define BUFF_SIZE 1024
#define TEMP_SIZE 4096
#define FD_MAX 7168
typedef struct 	s_fd
{
	char	*tmp;
	size_t	mem_size;
	char	*nl;
}		t_fd;
#endif
