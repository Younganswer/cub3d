#include "../../incs/game.h"
#include <math.h>
#include <stdlib.h>

const static double	g_move_speed = 0.03;
const static double	g_correction_dist = 0.2;
const static double	g_offset = 0.01;

int				key_pressed(int keycode, t_game *game);
static t_bool	move(t_game *game, double dx, double dy);
static t_bool	set_next_x(t_game *game, t_coord *next, double dx);
static t_bool	set_next_y(t_game *game, t_coord *next, double dy);

int	key_pressed(int keycode, t_game *game)
{
	const double	dx = game->player->dir.x * g_move_speed;
	const double	dy = game->player->dir.y * g_move_speed;

	if (keycode == KEY_ESC)
		exit_game(game);
	if (keycode == KEY_W)
		move(game, dx, dy);
	else if (keycode == KEY_S)
		move(game, -dx, -dy);
	else if (keycode == KEY_A)
		move(game, -dy, dx);
	else if (keycode == KEY_D)
		move(game, dy, -dx);
	return (0);
}

static t_bool	move(t_game *game, double dx, double dy)
{
	t_player *const	player = game->player;
	t_coord *const	next = ft_calloc(sizeof(t_coord), 1, "");

	if (set_next_x(game, next, dx) == FALSE || \
		set_next_y(game, next, dy) == FALSE)
		return (FALSE);
	player->pos.x = next->x;
	player->pos.y = next->y;
	free(next);
	return (TRUE);
}

static t_bool	set_next_x(t_game *game, t_coord *next, double dx)
{
	const double	cur_x = game->player->pos.x;
	const double	cur_y = game->player->pos.y;

	next->x = cur_x + dx;
	if ((dx < 0) && (next->x - (int)cur_x < g_correction_dist) && \
		((game->worldmap->map[(int)(cur_x - 1)][(int)cur_y] == '1') || \
		((cur_y - (int)cur_y < g_correction_dist - g_offset) && \
		(game->worldmap->map[(int)(cur_x - 1)][(int)(cur_y - 1)] == '1')) || \
		((1 - g_correction_dist + g_offset < cur_y - (int)cur_y) && \
		(game->worldmap->map[(int)(cur_x - 1)][(int)(cur_y + 1)] == '1'))))
		next->x = (int)cur_x + g_correction_dist;
	else if ((0 <= dx) && (1 - g_correction_dist < next->x - (int)cur_x) && \
		((game->worldmap->map[(int)(cur_x + 1)][(int)cur_y] == '1') || \
		((cur_y - (int)cur_y < g_correction_dist - g_offset) && \
		(game->worldmap->map[(int)(cur_x + 1)][(int)(cur_y - 1)] == '1')) || \
		((1 - g_correction_dist + g_offset < cur_y - (int)cur_y) && \
		(game->worldmap->map[(int)(cur_x + 1)][(int)(cur_y + 1)] == '1'))))
		next->x = (int)(cur_x + 1) - g_correction_dist;
	return (TRUE);
}

static t_bool	set_next_y(t_game *game, t_coord *next, double dy)
{
	const double	cur_x = game->player->pos.x;
	const double	cur_y = game->player->pos.y;

	next->y = cur_y + dy;
	if ((dy < 0) && (next->y - (int)cur_y < g_correction_dist) && \
		((game->worldmap->map[(int)cur_x][(int)(cur_y - 1)] == '1') || \
		((cur_x - (int)cur_x < g_correction_dist - g_offset) && \
		(game->worldmap->map[(int)(cur_x - 1)][(int)(cur_y - 1)] == '1')) || \
		((1 - g_correction_dist + g_offset < cur_x - (int)cur_x) && \
		(game->worldmap->map[(int)(cur_x + 1)][(int)(cur_y - 1)] == '1'))))
		next->y = (int)cur_y + g_correction_dist;
	else if ((0 <= dy) && (1 - g_correction_dist < next->y - (int)cur_y) && \
		((game->worldmap->map[(int)cur_x][(int)(cur_y + 1)] == '1') || \
		((cur_x - (int)cur_x < g_correction_dist - g_offset) && \
		(game->worldmap->map[(int)(cur_x - 1)][(int)(cur_y + 1)] == '1')) || \
		((1 - g_correction_dist + g_offset < cur_x - (int)cur_x) && \
		(game->worldmap->map[(int)(cur_x + 1)][(int)(cur_y + 1)] == '1'))))
		next->y = (int)(cur_y + 1) - g_correction_dist;
	return (TRUE);
}
