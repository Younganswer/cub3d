#include "../../incs/parse.h"
#include <stdlib.h>

t_bool			parse_floor_ceiling(t_game *var, int fd);
static t_bool	set_color(int color[3], char *line);
static t_bool	del_string(char **str);

t_bool	parse_floor_ceiling(t_game *var, int fd)
{
	t_bool	ret;
	size_t	i;
	char	*line;

	i = 0;
	while (i < 2)
	{
		line = read_line(fd);
		if (line == NULL)
			return (FALSE);
		if (*line == 'F')
			ret = set_color(var->floor.color, line + 2);
		else if (*line == 'C')
			ret = set_color(var->ceiling.color, line + 2);
		else
			ret = FALSE;
		free(line);
		if (ret == FALSE)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static t_bool	set_color(int color[3], char *line)
{
	char **const	rgb = ft_split(line, ',');
	size_t			i;

	if (rgb == NULL)
		return (FALSE);
	i = 0;
	while (i < 3)
	{
		color[i] = ft_atoi(rgb[i]);
		if (color[i] < 0 || 255 < color[i])
			return (del_string(rgb) == FALSE);
		i++;
	}
	return (del_string(rgb) == TRUE);
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
