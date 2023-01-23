#include "../libs/libmlx/incs/mlx.h"
#include "../incs/structs.h"
#include "../incs/parse.h"
#include "../incs/game.h"
#include "../incs/render.h"
#include <stdlib.h>

int	main(int argc, char **argv)
{
	t_game *const	game = ft_calloc(sizeof(t_game), 1, "");

	if (argc != 2)
		return (0 < ft_putendl_fd("Usage: ./cub3d mapfile.cub", 1));
	if (init_game(game, argv[1]) == FALSE)
		ft_exit_with_error("Error: Failed to initialize game", 1);
	mlx_hook(game->mlx->window, ON_DESTROY, 0, exit_game, game);
	mlx_hook(game->mlx->window, ON_KEYDOWN, 0, key_pressed, game);
	mlx_hook(game->mlx->window, ON_MOUSEMOVE, 0, mouse_moved, game);
	mlx_loop_hook(game->mlx->mlx, render, game);
	mlx_loop(game->mlx->mlx);
	return (0);
}