#include "../../incs/game.h"
#include "../../incs/parse.h"
#include "../../libs/mlx/incs/mlx.h"

t_bool	init_game(t_game *game, char *file);

t_bool	init_game(t_game *game, char *file)
{
	if (parse(game, file) == FALSE)
		return (FALSE);
	game->mlx = mlx_init();
	if (game->mlx == NULL)
		ft_exit_with_error("Error: Failed to initialize mlx", 1);
	game->window = mlx_new_window(
			game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d");
	if (game->window == NULL)
		ft_exit_with_error("Error: Failed to initialize window", 1);
	return (TRUE);
}
