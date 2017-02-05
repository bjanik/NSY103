#include "lib.h"

int	create_shm(size_t size)
{
	key_t	key;
	
	key = ftok(KEY_PATH, 0);
	return (shmget(key, size, 0600 | IPC_CREAT | IPC_EXCL));
}

