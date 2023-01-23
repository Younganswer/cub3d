#ifndef STRUCTS_H
# define STRUCTS_H

# include "../libs/libft/incs/libft.h"

# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080

typedef enum	e_direction
{
	NO = 0,
	SO = 1,
	WE = 2,
	EA = 3,
}	t_direction;

typedef struct	s_texture
{
	char	*file;
}	t_texture;

typedef struct	s_mlx
{
	void	*mlx;
	void	*window;
	void	*img_to_render;
	void	*img_buffer;
}	t_mlx;

typedef struct	s_space
{
	t_texture	*walls;
	size_t		floor_color;
	size_t		ceiling_color;
}	t_space;

typedef struct	s_game
{
	t_mlx		*mlx;
	t_space		*space;
	t_list		*map;
}	t_game;

#endif