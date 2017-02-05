#include "lib.h"

void	set_nb_places(t_req_res *res, char *nb_places)
{
	if (res != NULL)
		res->nb_places_res = atoi(nb_places);
}

