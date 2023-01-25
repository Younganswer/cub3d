#include "../../incs/render.h"

t_bool	render_line(t_game *game, int col);

t_bool	render_line(t_game *game, int col)
{
	t_raycast *const	raycast = game->raycast[col];
	int					i;
	size_t				color;

	i = 0;
	while (i < SCREEN_HEIGHT)
	{
		if (i < raycast->draw_start)
			color = 0x00FFFFFF;
		else if (raycast->draw_end < i)
			color = 0x00000000;
		else
			color = raycast->color;
		game->img->data[i * SCREEN_WIDTH + col] = color;
		i++;
	}
	return (TRUE);
}