#include "../../incs/parse.h"
#include "../../libs/libgnl/incs/get_next_line.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

t_bool	parse(t_game *game, char *file);
char	*get_next_line_which_is_not_empty(int fd);

t_bool	parse(t_game *game, char *file)
{
	const int	fd = open(file, O_RDONLY);
	t_bool		ret;

	ret = FALSE;
	if (fd == -1)
		return (ret);
	game->space = ft_calloc(sizeof(t_space), 1, "");
	if (parse_texture(game->space, fd) && \
		parse_floor_ceiling(game->space, fd) && \
		parse_map(game, fd))
		ret = TRUE;
	close(fd);
	return (TRUE);
}

char	*get_next_line_which_is_not_empty(int fd)
{
	char	*ret;

	ret = get_next_line(fd);
	if (ret == NULL)
		return (NULL);
	while (*ret == '\n')
	{
		free(ret);
		ret = get_next_line(fd);
		if (ret == NULL)
			return (NULL);
	}
	return (ret);
}
