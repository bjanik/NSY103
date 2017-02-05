#include "lib.h"

int	create_msgq(void)
{
	key_t	key;

	key = ftok(KEY_PATH, 0);
	return (msgget(key, IPC_CREAT | 0660));
}
