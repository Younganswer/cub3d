#ifndef GAME_H
# define GAME_H

#include "structs.h"

// exit_game.c
int		exit_game(t_game *game);
t_bool	set_err_code(t_game *game, t_err err_code);

// handle_key_event.c
int		key_pressed(int keycode, t_game *game);
int		key_released(int keycode, t_game *game);

// handle_mouse_event.c
int		mouse_moved(int x, int y, t_game *game);
t_bool	set_new_dir(t_player *player, int dir);

// init_game.c
t_bool	init_game(t_game *game, char *file);

// move.c
t_bool	move(t_game *game);

#endif