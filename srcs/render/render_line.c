#include "../../incs/render.h"

t_bool	render_line(t_game *game, int col);

t_bool	render_line(t_game *game, int col)
{
	t_raycast *const	raycast = game->raycast[col];
	int					i;

	i = raycast->draw_start;
	while (i < raycast->draw_end)
	{
		game->img->data[i * SCREEN_WIDTH + col] = raycast->color;
		i++;
	}
	return (TRUE);
}