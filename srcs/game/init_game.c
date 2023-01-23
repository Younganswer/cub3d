#include "../../incs/game.h"
#include "../../incs/parse.h"
#include "../../libs/libmlx/incs/mlx.h"

t_bool			init_game(t_game *game, char *file);
static t_bool	init_mlx(t_game *game);

t_bool	init_game(t_game *game, char *file)
{
	if (parse(game, file) == FALSE)
		return (FALSE);
	if (init_mlx(game) == FALSE)
		return (FALSE);
	return (TRUE);
}

static t_bool	init_mlx(t_game *game)
{
	game->mlx = ft_calloc(sizeof(t_mlx), 1, "");
	game->mlx->mlx = mlx_init();
	if (game->mlx->mlx == NULL)
		return (FALSE);
	game->mlx->window = \
		mlx_new_window(game->mlx->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D");
	if (game->mlx->window == NULL)
		return (FALSE);
	return (TRUE);
}
