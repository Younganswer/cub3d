#ifndef STRUCTS_H
# define STRUCTS_H

# include "../libs/libft/incs/libft.h"

# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080

typedef struct	s_texture
{
	char	*file;
}	t_texture;

typedef struct	s_color
{
	int	color[3];
}	t_color;

typedef struct	s_game
{
	void		*mlx;
	void		*window;
	void		*img_to_render;
	void		*img_buffer;
	t_list		*map;
	t_texture	*texture;
	t_color		floor;
	t_color		ceiling;
}	t_game;

#endif