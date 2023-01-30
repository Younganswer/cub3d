#include "../../incs/game.h"
#include "../../libs/libmlx/incs/mlx.h"
#include <math.h>

const double	g_rot_speed = 0.01;

int		mouse_moved(int x, int y, t_game *game);
t_bool	set_new_dir(t_player *player, int dir);

int	mouse_moved(int x, int y, t_game *game)
{
	int	dir;

	dir = 0;
	if (x < game->img->width / 2 - 4)
		dir = 1;
	else if (game->img->width / 2 + 4 < x)
		dir = -1;
	set_new_dir(game->player, dir);
	mlx_mouse_move(
		game->mlx->window,
		game->img->width / 2,
		game->img->height / 2
		);
	(void) y;
	return (0);
}

t_bool	set_new_dir(t_player *player, int dir)
{
	const t_coord	old_dir = player->dir;
	const t_coord	old_plane = player->plane;

	if (dir == 0)
		return (TRUE);
	player->dir.x = old_dir.x * cos(dir * g_rot_speed)
		- old_dir.y * sin(dir * g_rot_speed);
	player->dir.y = old_dir.x * sin(dir * g_rot_speed)
		+ old_dir.y * cos(dir * g_rot_speed);
	player->plane.x = old_plane.x * cos(dir * g_rot_speed)
		- old_plane.y * sin(dir * g_rot_speed);
	player->plane.y = old_plane.x * sin(dir * g_rot_speed)
		+ old_plane.y * cos(dir * g_rot_speed);
	return (TRUE);
}
