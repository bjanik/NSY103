#include "lib.h"

void	display_message_cons(t_req_cons *cons)
{
	if (cons != NULL)
		printf("mtype = %ld\nSpectacle = %s\npid = %d\n", cons->mtype, cons->spectacle, cons->pid);
}
