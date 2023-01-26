#include "../../incs/parse.h"
#include <stdlib.h>

t_bool			parse_floor_ceiling(t_game *game, int fd);
static t_bool	set_color(size_t *color, char *line);
static t_bool	del_string(char **str);

t_bool	parse_floor_ceiling(t_game *game, int fd)
{
	t_space *const	space = game->space;
	t_bool	ret;
	size_t	i;
	char	*line;

	i = 0;
	while (i++ < 2)
	{
		ret = TRUE;
		line = get_next_line_which_is_not_empty(fd);
		if (line == NULL)
			return (FALSE);
		if ((*line != 'C' && *line != 'F') || \
			(*line == 'C' && set_color(&space->ceiling_color, line + 2) == FALSE) || \
			(*line == 'F' && set_color(&space->floor_color, line + 2) == FALSE))
			ret = FALSE;
		free(line);
		if (ret == FALSE)
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

static t_bool	del_string(char **str)
{
	char	**tmp;

	if (str == NULL)
		return (TRUE);
	tmp = str;
	while (*tmp)
		free(*tmp++);
	free(str);
	return (TRUE);
}
