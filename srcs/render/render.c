#include "../../incs/render.h"
#include "../../incs/raycast.h"

int	render(t_game *game);

int	render(t_game *game)
{
	raycast(game);
	return (0);
}
