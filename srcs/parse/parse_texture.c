#include "../../incs/parse.h"
#include "../../incs/game.h"
#include "../../libs/libmlx/incs/mlx.h"
#include <stdlib.h>
#include <fcntl.h>

t_bool			parse_texture(t_game *game, int fd);
t_bool			texture_xpm_to_img(t_game *game);
static t_bool	set_texture_file_path(t_game *game, int fd);
static int		get_idx(char *dir);

t_bool	parse_texture(t_game *game, int fd)
{
	game->space->walls = ft_calloc(sizeof(t_texture), 4, "");
	return (set_texture_file_path(game, fd));
}

static t_bool	set_texture_file_path(t_game *game, int fd)
{
	t_texture *const	walls = game->space->walls;
	size_t				i;
	int					idx;
	char				*line;

	i = 0;
	while (i++ < 4)
	{
		line = get_next_line_which_is_not_empty(fd);
		if (line == NULL)
			return (set_err_code(game, FILE_ERR) == FALSE);
		idx = get_idx(line);
		if (0 <= idx)
			walls[idx].file = ft_substr(line + 3, 0, ft_strlen(line + 3) - 1);
		free(line);
		if (idx < 0)
			return (set_err_code(game, IDENTIFIER_ERR) == FALSE);
		else if (check_file_extension(walls[idx].file, ".xpm") == FALSE)
			return (set_err_code(game, FILE_ERR) == FALSE);
	}
	return (TRUE);
}

static int	get_idx(char *dir)
{
	if (ft_strncmp(dir, "NO ", 3) == 0)
		return (0);
	else if (ft_strncmp(dir, "SO ", 3) == 0)
		return (1);
	else if (ft_strncmp(dir, "WE ", 3) == 0)
		return (2);
	else if (ft_strncmp(dir, "EA ", 3) == 0)
		return (3);
	return (-1);
}

t_bool	texture_xpm_to_img(t_game *game)
{
	t_texture	*wall;
	size_t		i;

	i = 0;
	while (i < 4)
	{
		wall = &game->space->walls[i];
		wall->img = ft_calloc(sizeof(t_img), 1, "");
		wall->img->img = mlx_xpm_file_to_image(
				game->mlx->mlx, wall->file,
				&wall->img->width, &wall->img->height);
		if (wall->img->img == NULL)
			return (set_err_code(game, FILE_ERR));
		wall->img->data = (unsigned int *) mlx_get_data_addr(
				wall->img->img, &wall->img->bits_per_pixel,
				&wall->img->size_line, &wall->img->endian);
		if (wall->img->data == NULL)
			return (set_err_code(game, IMG_ERR));
		i++;
	}
	return (TRUE);
}
