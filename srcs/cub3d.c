#include "../libs/libmlx/incs/mlx.h"
#include "../incs/structs.h"
#include "../incs/parse.h"
#include "../incs/game.h"
#include "../incs/render.h"
#include <stdlib.h>

static void	exit_with_error(t_game *game);

int	main(int argc, char **argv)
{
	t_game *const	game = ft_calloc(sizeof(t_game), 1, "");

	if (argc != 2)
		return (0 < ft_putendl_fd("Usage: ./cub3d mapfile.cub", 1));
	if (init_game(game, argv[1]) == FALSE)
		exit_with_error(game);
	mlx_hook(game->mlx->window, ON_DESTROY, 0, exit_game, game);
	mlx_hook(game->mlx->window, ON_KEYDOWN, 0, key_pressed, game);
	mlx_hook(game->mlx->window, ON_MOUSEMOVE, 0, mouse_moved, game);
	mlx_loop_hook(game->mlx->mlx, render, game);
	mlx_loop(game->mlx->mlx);
	return (0);
}

static void	exit_with_error(t_game *game)
{
	ft_putendl_fd("Error", 2);
	if (game->err == MLX_ERR)
		ft_exit_with_error("Failed to initialize mlx", MLX_ERR);
	else if (game->err == IMG_ERR)
		ft_exit_with_error("Failed to initialize image", IMG_ERR);
	else if (game->err == FILE_ERR)
		ft_exit_with_error("Failed to open file", FILE_ERR);
	else if (game->err == IDENTIFIER_ERR)
		ft_exit_with_error("Invalid identifier", IDENTIFIER_ERR);
	else if (game->err == RGB_ERR)
		ft_exit_with_error("Invalid RGB value", RGB_ERR);
	else if (game->err == PLAYER_ERR)
		ft_exit_with_error("Player does not exist", PLAYER_ERR);
	else if (game->err == NON_ALLOWED_CHAR_ERR)
		ft_exit_with_error("Non-allowed character is used",
			NON_ALLOWED_CHAR_ERR);
	else if (game->err == MAP_BOARDER_ERR)
		ft_exit_with_error("Map is not closed", MAP_BOARDER_ERR);
}
