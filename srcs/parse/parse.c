#include "../../incs/parse.h"
#include "../../libs/libgnl/incs/get_next_line.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

t_bool	parse(t_game *var, char *file);
char	*read_line(int fd);

t_bool	parse(t_game *var, char *file)
{
	const int	fd = open(file, O_RDONLY);
	t_bool		ret;

	if (fd == -1)
		return (FALSE);
	ret = TRUE;
	if (parse_texture(var, fd) == FALSE)
		ret = (printf("Error: Failed to parse texture") < 0);
	else if (parse_floor_ceiling(var, fd) == FALSE)
		ret = (printf("Error: Failed to parse floor and ceiling color") < 0);
	else if (parse_map(var, fd) == FALSE)
		ret = (printf("Error: Failed to parse map") < 0);
	close(fd);
	return (ret);
}

char	*read_line(int fd)
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
