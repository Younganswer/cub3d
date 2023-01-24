#include "../../incs/render.h"
#include "../../incs/raycast.h"
#include "../../libs/libmlx/incs/mlx.h"

int	render(t_game *game);

int	render(t_game *game)
{
	int	col;

	col = 0;
	while (col < SCREEN_WIDTH)
	{
		if (raycast(game, col) == FALSE || \
			render_line(game, col) == FALSE)
			return (0);
		col++;
	}
	mlx_put_image_to_window(game->mlx->mlx, game->mlx->window, game->img->img, 0, 0);
	return (0);
}
