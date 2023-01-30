#include "../../incs/parse.h"
#include "../../incs/game.h"
#include <stdlib.h>

t_bool			parse_floor_ceiling(t_game *game, int fd);
static t_bool	set_color(size_t *color, char *line);

t_bool	parse_floor_ceiling(t_game *game, int fd)
{
	t_space *const	space = game->space;
	size_t			i;
	char			*line;

	i = 0;
	while (i++ < 2)
	{
		line = get_next_line_which_is_not_empty(fd);
		if (line == NULL)
			return (FALSE);
		if (*line != 'C' && *line != 'F')
			set_err_code(game, IDENTIFIER_ERR);
		else if (
			(*line == 'C' && !set_color(&space->ceiling_color, line + 2)) || \
			(*line == 'F' && !set_color(&space->floor_color, line + 2)))
			set_err_code(game, RGB_ERR);
		free(line);
		if (game->err != 0)
			return (FALSE);
	}
	return (TRUE);
}

static t_bool	set_color(size_t *color, char *line)
{
	char **const	rgb = ft_split(line, ',');
	size_t			i;
	int				c;

	if (rgb == NULL)
		return (FALSE);
	i = 0;
	while (i < 3)
	{
		c = ft_atoi(rgb[i++]);
		if (c < 0 || 255 < c)
			return (del_string(rgb) == FALSE);
		*color = (*color << 8) + c;
	}
	return (del_string(rgb));
}
