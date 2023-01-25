#include "../../incs/game.h"
#include "../../libs/libmlx/incs/mlx.h"
#include <stdio.h>
#include <math.h>

const double	rot_speed = 0.015;

int	mouse_moved(int x, int y, t_game *game);

int	mouse_moved(int x, int y, t_game *game)
{
	t_player *const	player = game->player;
	const t_coord	old_dir = player->dir;
	const t_coord	old_plane = player->plane;

	printf("x: %d\n", x - SCREEN_WIDTH / 2);
	if (SCREEN_WIDTH / 2 + 4 < x)
	{
		player->dir.x = player->dir.x * cos(-rot_speed) - player->dir.y * sin(-rot_speed);
		player->dir.y = old_dir.x * sin(-rot_speed) + player->dir.y * cos(-rot_speed);
		player->plane.x = player->plane.x * cos(-rot_speed) - player->plane.y * sin(-rot_speed);
    	player->plane.y = old_plane.x * sin(-rot_speed) + player->plane.y * cos(-rot_speed);
	}
	else if (x < SCREEN_WIDTH / 2 - 4)
	{
		player->dir.x = player->dir.x * cos(rot_speed) - player->dir.y * sin(rot_speed);
		player->dir.y = old_dir.x * sin(rot_speed) + player->dir.y * cos(rot_speed);
		player->plane.x = player->plane.x * cos(rot_speed) - player->plane.y * sin(rot_speed);
    	player->plane.y = old_plane.x * sin(rot_speed) + player->plane.y * cos(rot_speed);
	}
	mlx_mouse_move(game->mlx->window, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	(void) y;
	return (0);
}
