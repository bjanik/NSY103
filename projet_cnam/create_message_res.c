#include "lib.h"

t_req_res	*create_message_res(t_req_res *res, char *nom_spectacle)
{
	if (res == NULL)
	{	
		if ((res = (t_req_res*)malloc(sizeof(t_req_res))) == NULL)
			return(NULL);
	}
	res->mtype = RESERVATION;
	strcpy(res->spectacle, nom_spectacle);
	res->pid = getpid();
	return (res);
}
