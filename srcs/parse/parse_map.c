#include "../../incs/parse.h"
#include "../../libs/libgnl/incs/get_next_line.h"

t_bool	parse_map(t_var *var, int fd);

t_bool	parse_map(t_var *var, int fd)
{
	char	*line;

	while (TRUE)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (ft_strrchr(line, '\n') != NULL)
			*ft_strrchr(line, '\n') = '\0';
		ft_lstadd_back(&var->map, ft_lstnew(line));
	}
	return (TRUE);
}
