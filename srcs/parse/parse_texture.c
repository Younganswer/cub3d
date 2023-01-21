#include "../../incs/parse.h"
#include <stdlib.h>

static const char	*g_direction[] = {
	"NO", "SO", "WE", "EA", NULL
};

t_bool			parse_texture(t_game *var, int fd);
static t_bool	set_texture_file(t_texture *texture, int fd);
static int		get_idx(char *dir);

t_bool	parse_texture(t_game *var, int fd)
{
	var->texture = ft_calloc(sizeof(t_texture), 4, "");
	if (set_texture_file(var->texture, fd) == FALSE)
		return (FALSE);
	return (TRUE);
}

static t_bool	set_texture_file(t_texture *texture, int fd)
{
	size_t	i;
	int		idx;
	char	*line;

	i = 0;
	while (i < 4)
	{
		line = get_next_line_which_is_not_empty(fd);
		if (line == NULL)
			return (FALSE);
		idx = get_idx(line);
		if (0 <= idx)
			texture[idx].file = ft_substr(line + 3, 0, ft_strlen(line + 3) - 1);
		free(line);
		if (idx == -1)
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
