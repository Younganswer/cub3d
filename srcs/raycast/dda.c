#include "../../incs/raycast.h"
#include <stdlib.h>
#include <stdio.h>

t_bool			dda(t_game *game, int col);
static t_bool	set_dda_var(t_game *game, int col);
static t_bool	dda_algorithm(t_game *game, int col);

t_bool	dda(t_game *game, int col)
{
	if (set_dda_var(game, col) == FALSE || \
		dda_algorithm(game, col) == FALSE)
		return (FALSE);
	return (TRUE);
}

static t_bool	set_dda_var(t_game *game, int col)
{
	t_raycast *const	raycast = game->raycast[col];

	raycast->step.x = 1;
	raycast->side_dist.x
		= (raycast->map.x + 1.0 - game->player->pos.x) * raycast->delta_dist.x;
	if (raycast->ray_dir.x < 0)
	{
		raycast->step.x = -1;
		raycast->side_dist.x
			= (game->player->pos.x - raycast->map.x) * raycast->delta_dist.x;
	}
	raycast->step.y = 1;
	raycast->side_dist.y
		= (raycast->map.y + 1.0 - game->player->pos.y) * raycast->delta_dist.y;
	if (raycast->ray_dir.y < 0)
	{
		raycast->step.y = -1;
		raycast->side_dist.y
			= (game->player->pos.y - raycast->map.y) * raycast->delta_dist.y;
	}
	return (TRUE);
}

static t_bool	dda_algorithm(t_game *game, int col)
{
	t_raycast *const	raycast = game->raycast[col];

	while (raycast->hit == FALSE)
	{
		if (raycast->side_dist.x < raycast->side_dist.y)
		{
			raycast->side_dist.x += raycast->delta_dist.x;
			raycast->map.x += raycast->step.x;
			raycast->side = FALSE;
		}
		else
		{
			raycast->side_dist.y += raycast->delta_dist.y;
			raycast->map.y += raycast->step.y;
			raycast->side = TRUE;
		}
		raycast->hit = game->worldmap->map[
			(int)raycast->map.x][(int)raycast->map.y] == '1';
	}
	return (TRUE);
}
