#include "lib.h"

void	display_message_res(t_req_res *res)
{
	if (res != NULL)
		printf("mtype = %ld\nSpectacle = %s\nnb_places_res = %d\npid = %d\n", res->mtype, res->spectacle,res->nb_places_res, res->pid);
}
