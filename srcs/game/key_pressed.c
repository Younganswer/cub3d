#include "../../incs/game.h"
#include <stdio.h>

const static double	move_speed = 0.03;

int				key_pressed(int keycode, t_game *game);
static t_bool	move(t_keycode keycode, t_game *game);

static int		print_game(int key, t_game *game);
static t_bool	print_space(t_game *game);
static t_bool	print_map(t_game *game);
static t_bool	print_player(t_game *game);

int	key_pressed(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		exit_game(game);
	if (keycode == KEY_RETURN)
		print_game(keycode, game);
	if (keycode == KEY_W || \
		keycode == KEY_A || \
		keycode == KEY_S || \
		keycode == KEY_D)
		move(keycode, game);
	return (0);
}

static t_bool	move(t_keycode keycode, t_game *game)
{
	if (keycode == KEY_W)
	{
		if (game->worldmap->map[(int)(game->player->pos.x + game->player->dir.x * move_speed)][(int)(game->player->pos.y)] == '0')
			game->player->pos.x += game->player->dir.x * move_speed;
		if (game->worldmap->map[(int)(game->player->pos.x)][(int)(game->player->pos.y + game->player->dir.y * move_speed)] == '0')
			game->player->pos.y += game->player->dir.y * move_speed;
	}
	else if (keycode == KEY_S)
	{
		if (game->worldmap->map[(int)(game->player->pos.x - game->player->dir.x * move_speed)][(int)(game->player->pos.y)] == '0')
			game->player->pos.x -= game->player->dir.x * move_speed;
		if (game->worldmap->map[(int)(game->player->pos.x)][(int)(game->player->pos.y - game->player->dir.y * move_speed)] == '0')
			game->player->pos.y -= game->player->dir.y * move_speed;
	}
	else if (keycode == KEY_A)
	{
		if (game->worldmap->map[(int)(game->player->pos.x - game->player->dir.y * move_speed)][(int)(game->player->pos.y)] == '0')
			game->player->pos.x -= game->player->dir.y * move_speed;
		if (game->worldmap->map[(int)(game->player->pos.x)][(int)(game->player->pos.y + game->player->dir.x * move_speed)] == '0')
			game->player->pos.y += game->player->dir.x * move_speed;
	}
	else if (keycode == KEY_D)
	{
		if (game->worldmap->map[(int)(game->player->pos.x + game->player->dir.y * move_speed)][(int)(game->player->pos.y)] == '0')
			game->player->pos.x += game->player->dir.y * move_speed;
		if (game->worldmap->map[(int)(game->player->pos.x)][(int)(game->player->pos.y - game->player->dir.x * move_speed)] == '0')
			game->player->pos.y -= game->player->dir.x * move_speed;
	}
	return (TRUE);
}

static int	print_game(int key, t_game *game)
{
	(void) key;
	print_space(game);
	print_map(game);
	print_player(game);
	return (TRUE);
}

static t_bool	print_space(t_game *game)
{
	printf("NORTH: %s\n", game->space->walls[0].file);
	printf("SOUTH: %s\n", game->space->walls[1].file);
	printf("WEST: %s\n", game->space->walls[2].file);
	printf("EAST: %s\n", game->space->walls[3].file);
	printf("FLOOR: (%lu, %lu, %lu)\n", game->space->floor_color >> 16 & 0xFF, (game->space->floor_color >> 8) & 0xFF, game->space->floor_color & 0xFF);
	printf("CEILING: (%lu, %lu, %lu)\n", game->space->ceiling_color >> 16 & 0xFF, (game->space->ceiling_color >> 8) & 0xFF, game->space->ceiling_color & 0xFF);
	return (TRUE);
}

static t_bool	print_map(t_game *game)
{
	size_t	i;

	i = 0;
	while (i < game->worldmap->height)
		printf("%s\n", game->worldmap->map[i++]);
	return (TRUE);
}

static t_bool	print_player(t_game *game)
{
	printf("PLAYER POS: (%f, %f)\n", game->player->pos.x, game->player->pos.y);
	printf("PLAYER DIR: (%f, %f)\n", game->player->dir.x, game->player->dir.y);
	return (TRUE);
}
