#include "../../incs/raycast.h"

t_bool			set_line(t_game *game, int col);
static t_bool	set_line_height(t_game *game, int col);
static t_bool	set_line_color(t_game *game, int col);

t_bool	set_line(t_game *game, int col)
{
	if (set_line_height(game, col) == FALSE || \
		set_line_color(game, col) == FALSE)
		return (FALSE);
	return (TRUE);
}

static t_bool	set_line_height(t_game *game, int col)
{
	t_raycast *const	raycast = game->raycast[col];

	raycast->perp_wall_dist = (raycast->map.x - game->player->pos.x
			+ (1 - raycast->step.x) / 2) / raycast->ray_dir.x;
	if (raycast->side == TRUE)
		raycast->perp_wall_dist = (raycast->map.y - game->player->pos.y
				+ (1 - raycast->step.y) / 2) / raycast->ray_dir.y;
	raycast->line_height = (int)(SCREEN_HEIGHT / raycast->perp_wall_dist);
	raycast->draw_start = (SCREEN_HEIGHT / 2) - (raycast->line_height / 2);
	if (raycast->draw_start < 0)
		raycast->draw_start = 0;
	raycast->draw_end = (SCREEN_HEIGHT / 2) + (raycast->line_height / 2);
	if (SCREEN_HEIGHT <= raycast->draw_end)
		raycast->draw_end = SCREEN_HEIGHT - 1;
	return (TRUE);
}

static t_bool	set_line_color(t_game *game, int col)
{
	t_raycast *const	raycast = game->raycast[col];

	if (raycast->side == FALSE)
	{
		if (raycast->ray_dir.x < 0)
			raycast->color = 0x00FF0000;
		else
			raycast->color = 0x0000FF00;
	}
	else
	{
		if (raycast->ray_dir.y < 0)
			raycast->color = 0x000000FF;
		else
			raycast->color = 0x00FFFF00;
	}
	return (TRUE);
}
