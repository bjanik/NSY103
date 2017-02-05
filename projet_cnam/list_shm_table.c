#include "projet.h"

void	list_shm_table(t_spectacle *ptr_shm)
{
	int	i;

	i = 0;
	while ((ptr_shm + i)->nom_spectacle[0])
	{
		printf("nom spectacle: %s. Places restantes: %d\n", (ptr_shm + i)->nom_spectacle, (ptr_shm + i)->nb_places);
		i++;
	}
}
