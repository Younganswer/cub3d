#ifndef PARSE_H
# define PARSE_H

# include "../libs/libft/incs/libft.h"
# include "structs.h"

// parse.c
t_bool	parse(t_game *var, char *file);
char	*get_next_line_which_is_not_empty(int fd);

// parse_floor_ceil.c
t_bool	parse_floor_ceiling(t_game *var, int fd);

// parse_map.c
t_bool	parse_map(t_game *var, int fd);

// parse_texture.c
t_bool	parse_texture(t_game *var, int fd);

#endif