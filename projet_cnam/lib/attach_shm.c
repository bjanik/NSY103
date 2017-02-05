#include "lib.h"

void	*attach_shm(void)
{
	key_t	key;
	int	shm_id;

	key = ftok(KEY_PATH, 0);
	if ((shm_id = shmget(key, 0, 0600 | IPC_CREAT)) < 0 )
		return NULL;
	return (void*)shmat(shm_id, NULL, 0);
}
