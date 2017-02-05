#include "get_next_line.h"


int		init(t_fd *p_fd)
{
	if (p_fd->tmp == NULL)
	{
		if ((p_fd->tmp = (char*)ft_memalloc(TEMP_SIZE + 1)) == NULL)
			return (0);
		p_fd->mem_size = TEMP_SIZE + 1;
		p_fd->nl = NULL;
	}
	return (1);
}

char	*ft_realloc(t_fd *p_fd, size_t *mem_size, int ret)
{
	char	*s;

	while (*mem_size < strlen(p_fd->tmp) + ret)
	{
		s = p_fd->tmp;
		*mem_size *= 2;
		p_fd->tmp = (char*)ft_memalloc(*mem_size);
		strcpy(p_fd->tmp, s);
		free(s);
	}
	return (p_fd->tmp);
}

int		check_fd(const int fd, t_fd *p_fd, char **line)
{
	int		ret;
	char	c;

	if (line == NULL)
		return (-1);
	if (p_fd->tmp != NULL)
		return (1);
	if ((ret = read(fd, &c, 1)) > -1)
	{
		if (init(p_fd) == 0)
			return (-1);
		if (ret > 0)
			(p_fd->tmp)[0] = c;
	}
	return (1);
}

int		gnl_return_value(t_fd *p_fd, int ret, char **line)
{
	if (ret == -1)
		return (-1);
	if (strlen(p_fd->tmp) > 0 && ret == 0)
	{
		if ((p_fd->nl = strchr(p_fd->tmp, '\n')) != NULL)
		{
			if ((*line = strndup(p_fd->tmp, p_fd->nl - p_fd->tmp)) == NULL)
				return (-1);
			strcpy(p_fd->tmp, p_fd->nl + 1);
		}
		else
		{
			if ((*line = strdup(p_fd->tmp)) == NULL)
				return (-1);
			(p_fd->tmp)[0] = '\0';
		}
	}
	else if (ret == 0 && strlen(p_fd->tmp) == 0)
		return (0);
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	char		buff[BUFF_SIZE + 1];
	int			ret;
	static t_fd	p_fd[FD_MAX];

	if (fd < 0 || fd >= FD_MAX || check_fd(fd, p_fd + fd, line) == -1)
		return (-1);
	*line = NULL;
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		if ((p_fd + fd)->mem_size < strlen((p_fd + fd)->tmp) + BUFF_SIZE)
			if (((p_fd + fd)->tmp = ft_realloc((p_fd + fd),
							&((p_fd + fd)->mem_size), ret)) == NULL)
				return (-1);
		strcat((p_fd + fd)->tmp, buff);
		if (((p_fd + fd)->nl = strchr((p_fd + fd)->tmp, '\n')) != NULL)
		{
			if ((*line = strndup((p_fd + fd)->tmp, (p_fd + fd)->nl
							- (p_fd + fd)->tmp)) == NULL)
				return (-1);
			strcpy((p_fd + fd)->tmp, (p_fd + fd)->nl + 1);
			break ;
		}
	}
	return (gnl_return_value((p_fd + fd), ret, line));
}
