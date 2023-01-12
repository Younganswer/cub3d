#ifndef PARSE_H
# define PARSE_H

# include "../libs/libft/incs/libft.h"
# include "structs.h"

// parse.c
t_bool	parse(t_var *var, char *file);

// parse_map.c
t_bool	parse_map(t_var *var, int fd);

// parse_texture.c
t_bool	parse_texture(t_var *var, int fd);

#endif