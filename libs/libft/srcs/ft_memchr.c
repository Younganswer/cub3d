#include "../incs/libft.h"
#include <stdlib.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*tmp;

	tmp = (unsigned char *) s;
	while (n--)
	{
		if (*tmp == (unsigned char) c)
			return ((void *) tmp);
		tmp++;
	}
	return (0);
}
