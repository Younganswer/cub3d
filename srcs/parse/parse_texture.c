#include "../../incs/parse.h"
#include <stdlib.h>

t_bool			parse_texture(t_space *space, int fd);
static t_bool	set_texture_file(t_texture *walls, int fd);
static int		get_idx(char *dir);

t_bool	parse_texture(t_space *space, int fd)
{
	space->walls = ft_calloc(sizeof(t_texture), 4, "");
	return (set_texture_file(space->walls, fd));
}

static t_bool	set_texture_file(t_texture *walls, int fd)
{
	size_t	i;
	int		idx;
	char	*line;

	i = 0;
	while (i++ < 4)
	{
		line = get_next_line_which_is_not_empty(fd);
		if (line == NULL)
			return (FALSE);
		idx = get_idx(line);
		if (0 <= idx)
			walls[idx].file = ft_substr(line + 3, 0, ft_strlen(line + 3) - 1);
		free(line);
		if (idx == -1)
			return (FALSE);
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
