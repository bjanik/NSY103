#include "lib.h"

int	remove_shm(void)
{
	key_t	key;
	int	shm_id;

	key = ftok(KEY_PATH, 0);
	shm_id = shmget(key, 0, 0600 | IPC_CREAT);
	return (shmctl(shm_id, IPC_RMID, NULL));
}
