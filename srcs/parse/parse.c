#include "../../incs/parse.h"
#include <unistd.h>
#include <fcntl.h>

t_bool	parse(t_var *var, char *file);

t_bool	parse(t_var *var, char *file)
{
	const int	fd = open(file, O_RDONLY);
	t_bool		ret;

	if (fd == -1)
		return (FALSE);
	ret = TRUE;
	if (ret == TRUE && parse_texture(var, fd) == FALSE)
		ret = FALSE;
	if (ret == TRUE && parse_map(var, fd) == FALSE)
		ret = FALSE;
	close(fd);
	return (ret);
}
