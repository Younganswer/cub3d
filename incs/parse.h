#ifndef PARSE_H
# define PARSE_H

# include "../libs/libft/incs/libft.h"
# include "structs.h"

// parse.c
t_bool	parse(t_game *game, char *file);
char	*get_next_line_which_is_not_empty(int fd);
t_bool	check_file_extension(char *file, char *ext);
t_bool	del_string(char **str);

// parse_floor_ceiling.c
t_bool	parse_floor_ceiling(t_game *game, int fd);

// parse_map.c
t_bool	parse_map(t_game *game, int fd);

// parse_texture.c
t_bool	parse_texture(t_game *game, int fd);

// validate_map.c
t_bool	validate_map(t_game *game);

#endif