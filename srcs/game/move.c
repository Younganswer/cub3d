#include "../../incs/game.h"
#include <math.h>
#include <stdlib.h>

const static double	g_move_speed = 0.015;
const static double	g_correction_dist = 0.2;
const static double	g_offset = 0.01;

t_bool			move(t_game *game);
static double	get_cur_move_speed(t_game *game);
static t_bool	move_to(t_game *game, double dx, double dy);
static t_bool	set_next_x(t_game *game, t_coord *next, double dx);
static t_bool	set_next_y(t_game *game, t_coord *next, double dy);

t_bool	move(t_game *game)
{
	const double	move_speed = get_cur_move_speed(game);
	const double	dx = game->player->dir.x * move_speed;
	const double	dy = game->player->dir.y * move_speed;

	if (game->key_pressed[KEY_W])
		move_to(game, dx, dy);
	if (game->key_pressed[KEY_S])
		move_to(game, -dx, -dy);
	if (game->key_pressed[KEY_A])
		move_to(game, -dy, dx);
	if (game->key_pressed[KEY_D])
		move_to(game, dy, -dx);
	if (game->key_pressed[KEY_LEFT])
		set_new_dir(game->player, 1);
	if (game->key_pressed[KEY_RIGHT])
		set_new_dir(game->player, -1);
	return (TRUE);
}

static double	get_cur_move_speed(t_game *game)
{
	const int	num_of_pressed_keys = \
		game->key_pressed[KEY_W] + game->key_pressed[KEY_S] + \
		game->key_pressed[KEY_A] + game->key_pressed[KEY_D];

	if (1 < num_of_pressed_keys)
		return (g_move_speed / sqrt(2));
	return (g_move_speed);
}

static t_bool	move_to(t_game *game, double dx, double dy)
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
