#include "../cub3d.h"

int	memory_error(void)
{
	perror("Error: Failed to allocate memory for game data");
	return (EXIT_FAILURE);
}
