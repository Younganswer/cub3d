#include "../../incs/parse.h"
#include "../../libs/libgnl/incs/get_next_line.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

t_bool	parse(t_var *var, char *file);
char	*read_line(int fd);

t_bool	parse(t_var *var, char *file)
{
	const int	fd = open(file, O_RDONLY);
	t_bool		ret;

	if (fd == -1)
		return (FALSE);
	ret = TRUE;
	if (ret == TRUE && parse_texture(var, fd) == FALSE)
		ret = FALSE;
	if (ret == TRUE && parse_floor_ceiling(var, fd) == FALSE)
		ret = FALSE;
	if (ret == TRUE && parse_map(var, fd) == FALSE)
		ret = FALSE;
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
