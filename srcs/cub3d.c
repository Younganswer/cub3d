#include <stdio.h>
#include "../incs/structs.h"
#include "../incs/parse.h"

static t_bool	init_var(t_var *var, char *file);
static t_bool	print_map(t_var *var);

int	main(int argc, char **argv)
{
	t_var	*var;

	var = NULL;
	if (argc != 2)
	{
		printf("Usage: ./cub3d mapfile.cub\n");
		return (1);
	}
	if (init_var(var, argv[1]) == FALSE)
	{
		printf("Error: Fail to initialize variables\n");
		return (1);
	}
	return (0);
}

static t_bool	init_var(t_var *var, char *file)
{
	var = ft_calloc(sizeof(t_var), 1, "");
	if (parse(var, file) == FALSE)
		return (FALSE);
	print_map(var);
	return (TRUE);
}

static t_bool	print_map(t_var *var)
{
	t_list	*tmp;

	tmp = var->map;
	while (tmp)
	{
		printf("%s\n", (char *) tmp->content);
		tmp = tmp->next;
	}
	return (TRUE);
}
