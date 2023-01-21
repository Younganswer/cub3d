#include "../incs/libft.h"
#include <stdlib.h>

void	ft_exit_with_error(const char *str, int exit_flag)
{
	if (str)
		ft_putendl_fd(str, 2);
	exit(exit_flag);
}
