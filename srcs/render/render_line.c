#include "../../incs/render.h"
#include <math.h>

t_bool			render_line(t_game *game, int col);
static size_t	get_texture_color(t_raycast *raycast, t_player *player, int r);

t_bool	render_line(t_game *game, int col)
{
	t_raycast *const	raycast = game->raycast[col];
	int					row;
	size_t				color;

	row = 0;
	while (row < game->img->height)
	{
		color = 0;
		if (row < raycast->draw_start)
			color = game->space->ceiling_color;
		else if (raycast->draw_end < row)
			color = game->space->floor_color;
		else
			color = get_texture_color(raycast, game->player, row);
		game->img->data[row * game->img->width + col] = color;
		row++;
	}
	return (TRUE);
}

static size_t	get_texture_color(t_raycast *raycast, t_player *player, int r)
{
	double	step;
	double	wall_pos;
	int		tex_row;
	int		tex_col;
	int		idx;

	step = 1.0 * raycast->texture->img->height / raycast->line_height;
	tex_row = (int)(step * (r - SCREEN_HEIGHT / 2 + raycast->line_height / 2));
	tex_row &= (raycast->texture->img->height - 1);
	if (raycast->side == FALSE)
		wall_pos = player->pos.y + raycast->perp_wall_dist * raycast->ray_dir.y;
	else
		wall_pos = player->pos.x + raycast->perp_wall_dist * raycast->ray_dir.x;
	wall_pos -= floor(wall_pos);
	tex_col = (int)(wall_pos * (double)raycast->texture->img->width);
	if ((0 < raycast->ray_dir.x && raycast->side == FALSE) || \
		(raycast->ray_dir.y < 0 && raycast->side == TRUE))
		tex_col = raycast->texture->img->width - tex_col - 1;
	idx = tex_row * raycast->texture->img->width + tex_col;
	return (raycast->texture->img->data[idx]);
}
