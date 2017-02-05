#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include "lib/lib.h"

#ifndef PROJET_H
#define PROJET_H
#define SPECTACLE_LEN	128
#define CONSULTATION 1
#define RESERVATION 2
#define MAXMSGDATA 256

#define SPECTACLE_LEN   128

typedef struct  s_spectacle
{
        char    nom_spectacle[SPECTACLE_LEN];
        size_t  nb_places;
}               t_spectacle;


typedef struct 	s_req_cons
{
	long	mtype;
	char	spectacle[SPECTACLE_LEN];
	pid_t	pid;
}		t_req_cons;

typedef struct 	s_ans_cons
{
	long	mtype_pid;
	int	nb_places;
}		t_ans_cons;

typedef struct 	s_req_res
{
	long	mtype;
	char	spectacle[SPECTACLE_LEN];
	int	nb_places_res;
	pid_t	pid;
}		t_req_res;

typedef struct 	s_ans_res
{
	long	mtype_pid;
	char	ans[128];
}		t_ans_res;

void            fill_shm_table(t_spectacle *ptr_shm, int nb_spectacles, char *filename, char *line);
void            list_shm_table(t_spectacle *ptr_shm);
t_spectacle	*search_spectacle(t_spectacle *ptr_shm, char *nom_spectacle);



#endif

