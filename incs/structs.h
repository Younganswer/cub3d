#ifndef STRUCTS_H
# define STRUCTS_H

# include "../libs/libft/incs/libft.h"

typedef struct	s_texture
{
	char	*path;
}	t_texture;

typedef struct	s_color
{
	int	color[3];
}	t_color;

typedef struct	s_var
{
	t_list		*map;
	t_texture	*texture;
	t_color		floor;
	t_color		ceil;
}	t_var;

#endif