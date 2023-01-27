#ifndef STRUCTS_H
# define STRUCTS_H

# include "../libs/libft/incs/libft.h"

# define SCREEN_WIDTH 1280
# define SCREEN_HEIGHT 720
// # define SCREEN_WIDTH 1920
// # define SCREEN_HEIGHT 1080

typedef enum e_x_event
{
	ON_KEYDOWN = 2,
	ON_MOUSEMOVE = 6,
	ON_DESTROY = 17,
}	t_x_event;

typedef enum e_keycode
{
	KEY_ESC = 53,
	KEY_RETURN = 36,
	KEY_W = 13,
	KEY_A = 0,
	KEY_S = 1,
	KEY_D = 2,
}	t_keycode;

typedef enum	e_direction
{
	NO = 0,
	SO = 1,
	WE = 2,
	EA = 3,
}	t_direction;

typedef struct c_coord
{
	double	x;
	double	y;
}	t_coord;

typedef struct c_player
{
	t_coord	pos;
	t_coord	dir;
	t_coord	plane;
}	t_player;

typedef struct	s_mlx
{
	void	*mlx;
	void	*window;
}	t_mlx;

typedef struct	s_worldmap
{
	char	**map;
	size_t	width;
	size_t	height;
}	t_worldmap;

typedef struct	s_img
{
	void	*img;
	int		*data;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}	t_img;

typedef struct	s_texture
{
	char	*file;
	t_img	*img;
}	t_texture;

typedef struct	s_space
{
	t_texture	*walls;
	size_t		floor_color;
	size_t		ceiling_color;
}	t_space;

typedef struct	s_raycast
{
	t_coord		ray_dir;
	t_coord		side_dist;
	t_coord		delta_dist;
	t_coord		step;
	t_coord		map;
	double		camera_x;
	double		perp_wall_dist;
	int			line_height;
	int			draw_start;
	int			draw_end;
	t_bool		hit;
	t_bool		side;
	t_texture	*texture;
}	t_raycast;

typedef struct	s_game
{
	t_mlx		*mlx;
	t_space		*space;
	t_img		*img;
	t_worldmap	*worldmap;
	t_player	*player;
	t_raycast	**raycast;
}	t_game;

#endif