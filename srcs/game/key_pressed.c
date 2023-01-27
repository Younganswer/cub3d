#include "../../incs/game.h"
#include <math.h>

const static double	g_move_speed = 0.03;

int				key_pressed(int keycode, t_game *game);
static t_bool	move_to(t_keycode keycode, t_game *game);
static t_bool	move(t_game *game, double dx, double dy);

int	key_pressed(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		exit_game(game);
	if (keycode == KEY_W || \
		keycode == KEY_A || \
		keycode == KEY_S || \
		keycode == KEY_D)
		move_to(keycode, game);
	return (0);
}

static t_bool	move_to(t_keycode keycode, t_game *game)
{
	const double	dx = game->player->dir.x * g_move_speed;
	const double	dy = game->player->dir.y * g_move_speed;

	if (keycode == KEY_W)
		move(game, dx, dy);
	else if (keycode == KEY_S)
		move(game, -dx, -dy);
	else if (keycode == KEY_A)
		move(game, -dy, dx);
	else if (keycode == KEY_D)
		move(game, dy, -dx);
	return (TRUE);
}

static t_bool	move(t_game *game, double dx, double dy)
{
	t_player *const	player = game->player;
	const double	correction_x = player->pos.x + (0.1) * (dx / fabs(dx));
	const double	correction_y = player->pos.y + (0.1) * (dy / fabs(dy));
	const double	new_x = player->pos.x + dx;
	const double	new_y = player->pos.y + dy;

	if (game->worldmap->map[(int)correction_x][(int)player->pos.y] == '0')
		player->pos.x = new_x;
	if (game->worldmap->map[(int)player->pos.x][(int)correction_y] == '0')
		player->pos.y = new_y;
	return (TRUE);
}
