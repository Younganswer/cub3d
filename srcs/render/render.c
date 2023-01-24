#include "../../incs/render.h"
#include "../../incs/raycast.h"

int	render(t_game *game);

int	render(t_game *game)
{
	int	col;

	col = 0;
	while (col < SCREEN_WIDTH)
	{
		if (raycast(game, col) == FALSE)
			return (0);
		col++;
	}
	return (0);
}
