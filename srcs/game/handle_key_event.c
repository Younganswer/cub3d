#include "../../incs/game.h"
#include <math.h>
#include <stdlib.h>

int	key_pressed(int keycode, t_game *game);
int	key_released(int keycode, t_game *game);

int	key_pressed(int keycode, t_game *game)
{
	if (128 <= keycode)
		return (0);
	game->key_pressed[keycode] = TRUE;
	if (game->key_pressed[KEY_ESC])
		exit_game(game);
	return (0);
}

int	key_released(int keycode, t_game *game)
{
	if (128 <= keycode)
		return (0);
	game->key_pressed[keycode] = FALSE;
	return (0);
}
