#include "../libs/libmlx/incs/mlx.h"
#include "../incs/structs.h"
#include "../incs/parse.h"
#include "../incs/game.h"
#include <stdio.h>
#include <stdlib.h>

static int		print_game(int key, t_game *game);
static t_bool	print_texture(t_game *game);
static t_bool	print_floor_ceiling(t_game *game);
static t_bool	print_map(t_game *game);

int	main(int argc, char **argv)
{
	t_game *const	game = ft_calloc(sizeof(t_game), 1, "");

	if (argc != 2)
		return (0 < ft_putendl_fd("Usage: ./cub3d mapfile.cub", 1));
	if (init_game(game, argv[1]) == FALSE)
		ft_exit_with_error("Error: Failed to initialize game", 1);
	mlx_hook(game->mlx->window, 2, 0, print_game, game);
	mlx_loop(game->mlx->mlx);
	return (0);
}

static int	print_game(int key, t_game *game)
{
	(void) key;
	print_texture(game);
	print_floor_ceiling(game);
	print_map(game);
	return (TRUE);
}

static t_bool	print_texture(t_game *game)
{
	printf("NORTH: %s\n", game->space->walls[0].file);
	printf("SOUTH: %s\n", game->space->walls[1].file);
	printf("WEST: %s\n", game->space->walls[2].file);
	printf("EAST: %s\n", game->space->walls[3].file);
	return (TRUE);
}

static t_bool	print_floor_ceiling(t_game *game)
{
	printf("FLOOR: (%lu, %lu, %lu)\n", game->space->floor_color >> 16 & 0xFF, (game->space->floor_color >> 8) & 0xFF, game->space->floor_color & 0xFF);
	printf("CEILING: (%lu, %lu, %lu)\n", game->space->ceiling_color >> 16 & 0xFF, (game->space->ceiling_color >> 8) & 0xFF, game->space->ceiling_color & 0xFF);
	return (TRUE);
}

static t_bool	print_map(t_game *game)
{
	t_list	*tmp;

	tmp = game->map;
	while (tmp)
	{
		printf("%s\n", (char *) tmp->content);
		tmp = tmp->next;
	}
	return (TRUE);
}
