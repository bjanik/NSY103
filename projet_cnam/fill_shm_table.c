#include "projet.h"

void	fill_shm_table(t_spectacle *ptr_shm, int nb_spectacles, char *filename ,char *line)
{
	int	i;
	int	fd;
	char		**tab;

	i = 0;
	if ((fd = open(filename, O_RDONLY)) < 0)
		exit(-1);
	while (i < nb_spectacles)
	{
		get_next_line(fd, &line);
		tab = (char**)ft_strsplit(line, ';');
		strcpy((ptr_shm + i)->nom_spectacle, tab[0]);
		(ptr_shm + i)->nb_places = atoi(tab[1]);
		free(line);
		free(tab[0]);
		free(tab[1]);
		i++;
	}
	(ptr_shm + i)->nom_spectacle[0] = 0;
	close(fd);
}
