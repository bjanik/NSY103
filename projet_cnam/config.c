#include "projet.h"
/*
void	*ft_memalloc(size_t size)
{
	void	*ptr;

	if ((ptr = malloc(size)) == NULL)
		return (NULL);
	memset(ptr, 0, size);
	return (ptr);
}
*/
size_t	get_nb_lines(char *line)
{
	int	fd;
	size_t	nb_lines;
	
	nb_lines = 0;	
	system("wc -l spectacles.txt > nb_lines");
	if ((fd = open("nb_lines", O_RDONLY)) < 0)
		exit(-1);
	if (get_next_line(fd, &line) == -1)
		exit(-1);
	if (line != NULL)
	{
		nb_lines = atoi(line);
		free(line);
	}
	close(fd);
	return (nb_lines);
}

int	main(int argc, char **argv)
{
	char		*line;
	size_t		nb_spectacles;
	t_spectacle	*ptr_shm;
	int	opt;
	
	ptr_shm = NULL;
	nb_spectacles = get_nb_lines(line);
	while ((opt = getopt(argc, argv, "dlc:")) != -1)
	{
        	switch (opt)
		{
        	case 'c':
			if ((create_shm((nb_spectacles + 1) * sizeof(t_spectacle))) < 0)
			{
				perror("create_shm");
				exit(-1);
			}
			if ((ptr_shm = attach_shm()) == NULL)
			{
				perror("shmat");
				exit(-1);
			}
			fill_shm_table(ptr_shm, nb_spectacles, optarg, line);
                	break;
        	case 'l':
			if (ptr_shm == NULL)
			{
				if ((ptr_shm = attach_shm()) ==  (t_spectacle*)-1)
				{
					perror("shmat");
					exit(-1);
				}
			}
			list_shm_table(ptr_shm);
                	break;
        	case 'd':
			if (remove_shm() != 0)
			{
				perror("remove_shm");
				exit(-1);
			}	
                	break;
               	default: 
                	fprintf(stderr, "Usage: %s [-c filename] [-l] [-d]\n",
                        	argv[0]);
                	exit(-1);
        	}
	}
	return (0);
}
