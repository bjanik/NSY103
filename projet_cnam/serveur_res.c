#include "projet.h"

char SEM_NAME[] = "CNAM_SEM_SHM";
sem_t           *mutex;

int	reservation(t_spectacle *ptr_spectacle, t_req_res *ptr_req_res)
{	
	sem_wait(mutex);
	if (ptr_spectacle->nb_places >ptr_req_res->nb_places_res)
		ptr_spectacle->nb_places -= ptr_req_res->nb_places_res;
	sleep(15);
	sem_post(mutex);
	return (ptr_spectacle->nb_places - ptr_req_res->nb_places_res);
}

int	main(int argc, char **argv)
{
	t_spectacle	*ptr_shm;
	t_spectacle	*ptr_spectacle;
	int		msgq_id;
	t_req_res	req_res;
	t_req_res	*ptr_req_res;
	t_ans_res	ans_res;
	int		ret;
	int		status;
	int		nb_fils;
	key_t		key;

	ptr_shm = NULL;
	ptr_spectacle = NULL;
	ptr_req_res = &req_res;
	nb_fils = 0;
	key = ftok(KEY_PATH, 0);
	if ((mutex = sem_open(SEM_NAME, O_CREAT, 0660, 1)) == SEM_FAILED)
	{
		perror("Can't create semaphore");
		sem_unlink(SEM_NAME);
		exit(-1);
	}
	if ((ptr_shm = attach_shm()) == ((t_spectacle*) -1))
	{
		perror("shmat");
		exit(-1);
	}
	if ((msgq_id = msgget(key, 0660 | IPC_CREAT)) < 0)
	{
		perror("msgget");
		exit(-1);
	}
	while(42)
	{
		if (msgrcv(msgq_id, (void*)&req_res, sizeof(t_req_res), RESERVATION, 0) < 0)
		{
			perror("msgrcv");
			exit(-1);
		}
		if ((ret = fork()) < 0)
		{
			perror("fork");
			exit(-1);
		}
		nb_fils++;
		if (ret == 0)
		{
			printf("After fork in son\n");
			ptr_spectacle = search_spectacle(ptr_shm, req_res.spectacle);
			if (ptr_spectacle == NULL)
				strcpy(ans_res.ans, "Spectacle inexistant\n");
			else
			{
				if (reservation(ptr_spectacle, ptr_req_res) < 0)
					strcpy(ans_res.ans, "Pas assez de places disponibles\n");
				else
					strcpy(ans_res.ans, "Nous confirmons la reservation de vos places\n");
			}
			ans_res.mtype_pid = (long)req_res.pid;
			if (msgsnd(msgq_id, (void*)&ans_res, sizeof(t_ans_res), 0) < 0)
			{
				perror("msgsnd");
				exit(-1);
			}
			list_shm_table(ptr_shm);
			sleep(30);
			exit(1);
		}
		else
		{
			int	cpt = nb_fils;
			while (cpt > 0)
			{
				cpt--;
				if (waitpid(0, &status, WNOHANG) > 0)
					nb_fils--;
			}
			printf("After wait in father\n");
		}
	}
	return(0);
}
