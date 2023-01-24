#include "../../incs/raycast.h"
#include <math.h>

t_bool			raycast(t_game *game, int col);
static t_bool	set_raycast_var(t_game *game, int col);

t_bool	raycast(t_game *game, int col)
{
	if (set_raycast_var(game, col) == FALSE || \
		dda(game, col) == FALSE || \
		set_line(game, col) == FALSE)
		return (FALSE);
	return (TRUE);
}

static t_bool	set_raycast_var(t_game *game, int col)
{
	t_raycast *const	raycast = game->raycast[col];
	t_player *const		player = game->player;

	raycast->camera_x = (double) 2 * col / SCREEN_WIDTH - 1;
	raycast->ray_dir = (t_coord){
		player->dir.x + player->plane.x * raycast->camera_x,
		player->dir.y + player->plane.y * raycast->camera_x
	};
	raycast->map = (t_coord){(int)player->pos.x, (int)player->pos.y};
	raycast->delta_dist = (t_coord){
		fabs(1 / raycast->ray_dir.x), fabs(1 / raycast->ray_dir.y)
	};
	raycast->hit = FALSE;
	return (TRUE);
}
