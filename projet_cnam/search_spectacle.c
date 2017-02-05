#include "projet.h"

t_spectacle	*search_spectacle(t_spectacle *ptr_shm, char *nom_spectacle)
{
	int	i;

	i = 0;
	while ((ptr_shm + i)->nom_spectacle[0])
	{
		if (strcmp((ptr_shm + i)->nom_spectacle, nom_spectacle) == 0)
			return (ptr_shm + i);
		i++;
	}
	return (NULL);
}
