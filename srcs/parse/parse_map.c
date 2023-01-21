#include "../../incs/parse.h"
#include <stdlib.h>

t_bool	parse_map(t_game *var, int fd);

t_bool	parse_map(t_game *var, int fd)
{
	char	*line;
	char	*row;

	while (TRUE)
	{
		line = read_line(fd);
		if (line == NULL)
			break ;
		if (ft_strrchr(line, '\n') != NULL)
			row = ft_substr(line, 0, ft_strlen(line) - 1);
		else
			row = ft_strdup(line);
		ft_lstadd_back(&var->map, ft_lstnew(row));
		free(line);
	}
	return (TRUE);
}
