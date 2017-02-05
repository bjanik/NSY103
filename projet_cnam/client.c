#include "projet.h"

int	create_msgq(void)
{
	key_t	key;

	key = ftok(KEY_PATH, 0);
	return (msgget(key, IPC_CREAT | 0660));
}

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

void	set_nb_places(t_req_res *res, char *nb_places)
{
	if (res != NULL)
		res->nb_places_res = atoi(nb_places);
}

void	display_message_cons(t_req_cons *cons)
{
	if (cons != NULL)
		printf("mtype = %ld\nSpectacle = %s\npid = %d\n", cons->mtype, cons->spectacle, cons->pid);
}

void	display_message_res(t_req_res *res)
{
	if (res != NULL)
		printf("mtype = %ld\nSpectacle = %s\nnb_places_res = %d\npid = %d\n", res->mtype, res->spectacle,res->nb_places_res, res->pid);
}

void	display_message_ans_res(t_ans_res *res)
{
	if (res != NULL)
		printf("Reponse = %s\n", res->ans);
}

void	display_message_ans_cons(t_ans_cons *cons)
{
	if (cons != NULL)
		printf("Nb_places restantes = %d\n", cons->nb_places);
}

int	main(int argc, char **argv)
{
	int		msgq_id;
	t_req_cons	*req_cons;
	t_req_res	*req_res;
	t_ans_cons	ans_cons;
	t_ans_res	ans_res;
	t_ans_cons	*ptr_ans_cons;	
	t_ans_res	*ptr_ans_res;	
	int		opt;
	
	req_cons = NULL;
	req_res = NULL;
	ptr_ans_cons = &ans_cons;
	ptr_ans_res = &ans_res;
	if ((msgq_id = create_msgq()) < 0)
	{
		perror("create_msgq");
		exit(-1);
	}
	while ((opt = getopt(argc, argv, "c:r:n:")) != -1)
	{
		switch(opt)
		{
		case 'c':
			if ((req_cons = create_message_cons(req_cons, optarg)) == NULL)
			{
				perror("create_message_cons");
				exit(-1);
			}
			break;
		case 'r':
			if ((req_res = create_message_res(req_res, optarg)) == NULL)
			{
				perror("create_message_res");
				exit(-1);
			}
		case 'n':
			set_nb_places(req_res, optarg);
			break;		
		default :
			fprintf(stderr, "Usage : %s [-c spectacle] [-r spectacle] [-n nombre_de_places]\n", argv[0]);
			exit(-1);
		}
	}
	if (req_cons != NULL)
	{
		msgsnd(msgq_id, (void*)req_cons, sizeof(t_req_cons), 0);
		msgrcv(msgq_id, (void*)ptr_ans_cons, sizeof(t_ans_cons), getpid(), 0); 
		display_message_ans_cons(ptr_ans_cons); 
	}
	if (req_res != NULL)
	{
		msgsnd(msgq_id, (void*)req_res, sizeof(t_req_res), 0);
		msgrcv(msgq_id, (void*)ptr_ans_res, sizeof(t_ans_res), getpid(), 0);
		display_message_ans_res(ptr_ans_res); 
	}
	return (0);
}
