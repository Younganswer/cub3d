#include "../../incs/game.h"
#include <stdlib.h>

int		exit_game(t_game *game);
t_bool	set_err_code(t_game *game, t_err err_code);

int	exit_game(t_game *game)
{
	exit(game->err);
}

t_bool	set_err_code(t_game *game, t_err err_code)
{
	game->err = err_code;
	return (TRUE);
}
