#include "../incs/structs.h"
#include "../incs/parse.h"
#include <stdio.h>
#include <stdlib.h>

static t_bool	init_var(t_var *var, char *file);

static t_bool	print_var(t_var *var);
static t_bool	print_texture(t_var *var);
static t_bool	print_floor_ceiling(t_var *var);
static t_bool	print_map(t_var *var);

int	main(int argc, char **argv)
{
	t_var *const	var = ft_calloc(sizeof(t_var), 1, "");

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
	if (parse(var, file) == FALSE)
		return (FALSE);
	print_var(var);
	return (TRUE);
}

static t_bool	print_var(t_var *var)
{
	print_texture(var);
	print_floor_ceiling(var);
	print_map(var);
	return (TRUE);
}

static t_bool	print_texture(t_var *var)
{
	printf("NORTH: %s\n", var->texture[0].file);
	printf("SOUTH: %s\n", var->texture[1].file);
	printf("WEST: %s\n", var->texture[2].file);
	printf("EAST: %s\n", var->texture[3].file);
	return (TRUE);
}

static t_bool	print_floor_ceiling(t_var *var)
{
	printf("FLOOR: (%d, %d, %d)\n", var->floor.color[0], var->floor.color[1], var->floor.color[2]);
	printf("CEILING: (%d, %d, %d)\n", var->ceiling.color[0], var->ceiling.color[1], var->ceiling.color[2]);
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
