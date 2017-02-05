#include "projet.h"

int	main(int argc, char **argv)
{
	t_spectacle	*ptr_shm;
	t_spectacle	*ptr_spectacle;
	int		msgq_id;
	char		filler[256];
	t_req_cons	req_cons;
	t_ans_cons	ans_cons;
	key_t		key;
	
	//memset(pipo, 65, 256);
	key = ftok(KEY_PATH, 0);	
	ptr_shm = NULL;
	ptr_spectacle = NULL;
	if ((ptr_shm = attach_shm()) == ((t_spectacle*) -1))
	{
		perror("shmat");
		exit(-1);
	}
	if ((msgq_id = msgget(key, 0660 | IPC_CREAT )) < 0)
	{
		perror("msgget");
		exit(-1);
	}
	printf("msgq_id = %d\n", msgq_id);
	if (msgrcv(msgq_id, (void*)&req_cons, sizeof(t_req_cons), CONSULTATION, 0) < 0)
	{
		perror("msgrcv");
		exit(-1);
	}
	ptr_spectacle = search_spectacle(ptr_shm, req_cons.spectacle);
	ans_cons.mtype_pid = req_cons.pid;
	ans_cons.nb_places = ptr_spectacle->nb_places; 
	printf("pid = %d ; nb_places restantes = %d\n", ans_cons.mtype_pid, ans_cons.nb_places);
	if (msgsnd(msgq_id, (void*)&ans_cons, sizeof(t_ans_cons), 0) < 0)
	{
		perror("msgsnd");
		exit(-1);
	}
	//list_shm_table(ptr_shm);
	return(0);
}
