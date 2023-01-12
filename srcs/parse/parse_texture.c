#include "../../incs/parse.h"
#include "../../libs/libgnl/incs/get_next_line.h"

static const char	*g_direction[] = {
	"NO", "SO", "WE", "EA", NULL
};

t_bool			parse_texture(t_var *var, int fd);
static t_bool	read_texture(t_var *var, int fd);
static t_bool	read_floor_ceil(t_var *var, int fd);
static int		get_idx(char *dir);
static t_bool	set_color(int color[3], char *line);

t_bool	parse_texture(t_var *var, int fd)
{
	if (read_texture(var, fd) == FALSE)
		return (FALSE);
	if (read_floor_ceil(var, fd) == FALSE)
		return (FALSE);
	free(get_next_line(fd));
	return (TRUE);
}

static t_bool	read_texture(t_var *var, int fd)
{
	size_t	i;
	int		idx;
	char	*line;

	var->texture = ft_calloc(sizeof(t_texture), 4, "");
	i = 0;
	while (i < 4)
	{
		line = get_next_line(fd);
		if (line == NULL)
			return (FALSE);
		idx = get_idx(line);
		if (0 < idx)
			var->texture[idx].path = ft_strdup(line + 3);
		free(line);
		if (idx == -1)
			return (FALSE);
		i++;
	}
	line = get_next_line(fd);
	free(line);
	return (TRUE);
}

static t_bool	read_floor_ceil(t_var *var, int fd)
{
	t_bool	ret;
	size_t	i;
	char	*line;

	i = 0;
	while (i < 2)
	{
		line = get_next_line(fd);
		if (line == NULL)
			return (FALSE);
		if (*line == 'F')
			ret = set_color(var->floor.color, line + 2);
		else if (*line == 'C')
			ret = set_color(var->ceil.color, line + 2);
		else
			ret = FALSE;
		free(line);
		if (ret == FALSE)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static int	get_idx(char *dir)
{
	size_t	i;

	i = 0;
	while (i < 4)
	{
		if (ft_strncmp(g_direction[i], dir, 2) == 0)
			return (i);
		i++;
	}
	return (-1);
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
		{
			free(rgb[0]);
			free(rgb[1]);
			free(rgb[2]);
			free(rgb);
			return (FALSE);
		}
		i++;
	}
	free(rgb[0]);
	free(rgb[1]);
	free(rgb[2]);
	free(rgb);
	return (TRUE);
}
