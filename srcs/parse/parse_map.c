#include "../../incs/parse.h"
#include <stdlib.h>

t_bool	parse_map(t_game *game, int fd);

t_bool	parse_map(t_game *game, int fd)
{
	char	*line;
	char	*row;

	while (TRUE)
	{
		line = get_next_line_which_is_not_empty(fd);
		if (line == NULL)
			break ;
		if (ft_strrchr(line, '\n') != NULL)
			row = ft_substr(line, 0, ft_strlen(line) - 1);
		else
			row = ft_strdup(line);
		ft_lstadd_back(&game->map, ft_lstnew(row));
		free(line);
	}
	return (TRUE);
}
