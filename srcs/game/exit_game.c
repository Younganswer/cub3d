#include "../../incs/game.h"
#include <stdlib.h>

int		exit_game(t_game *game);
t_bool	set_err_code(t_game *game, t_err err_code);

int	exit_game(t_game *game)
{
	(void) game;
	exit(0);
}

t_bool	set_err_code(t_game *game, t_err err_code)
{
	game->err = err_code;
	return (TRUE);
}