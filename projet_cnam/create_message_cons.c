#include "lib.h"

t_req_cons	*create_message_cons(t_req_cons *cons, char *nom_spectacle)
{
	if (cons == NULL)
	{
		if ((cons = (t_req_cons*)malloc(sizeof(t_req_cons))) == NULL)
			return(NULL);
	}
	cons->mtype = CONSULTATION;
	strcpy(cons->spectacle, nom_spectacle);
	cons->pid = getpid();
	return (cons);
}
