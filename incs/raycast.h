#ifndef RAYCAST_H
# define RAYCAST_H

# include "structs.h"

// raycast.c
t_bool	raycast(t_game *game, int col);

// dda.c
t_bool	dda(t_game *game, int col);

// set_line.c
t_bool	set_line(t_game *game, int col);

#endif