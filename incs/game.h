#ifndef GAME_H
# define GAME_H

#include "structs.h"

// exit_game.c
int		exit_game(t_game *game);

// init_game.c
t_bool	init_game(t_game *game, char *file);

// key_pressed.c
int		key_pressed(int keycode, t_game *game);

// mouse_moved.c
int		mouse_moved(int x, int y, t_game *game);

#endif