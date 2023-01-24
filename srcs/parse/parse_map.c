#include "../../incs/parse.h"
#include <stdlib.h>

t_bool			parse_map(t_game *game, int fd);
static t_bool	read_map(t_game *game, t_list *tmp_map, int fd);
static t_bool	list_to_string_arr(t_game *game, t_list *tmp_map);

t_bool	parse_map(t_game *game, int fd)
{
	t_list	*tmp_map;

	tmp_map = NULL;
	game->worldmap = ft_calloc(sizeof(t_list *), 1, "");
	if (read_map(game, tmp_map, fd) == FALSE)
		return (FALSE);
	if (list_to_string_arr(game, tmp_map) == FALSE)
		return (FALSE);
	ft_lstclear(&tmp_map, free);
	return (TRUE);
}

static t_bool	read_map(t_game *game, t_list *tmp_map, int fd)
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
		ft_lstadd_back(&tmp_map, ft_lstnew(row));
		if (game->worldmap->width < ft_strlen(row))
			game->worldmap->width = ft_strlen(row);
		free(line);
		game->worldmap->height++;
	}
	return (TRUE);
}

static t_bool	list_to_string_arr(t_game *game, t_list *tmp_map)
{
	const size_t	width = game->worldmap->width;
	t_list			*tmp;
	char			*row;
	int				i;

	game->worldmap->map = ft_calloc(sizeof(char *), game->worldmap->height, "");
	tmp = tmp_map;
	i = 0;
	while (tmp != NULL)
	{
		row = ft_calloc(sizeof(char), width, "");
		ft_strlcpy(row, tmp->content, ft_strlen(tmp->content) + 1);
		ft_memset(row + ft_strlen(tmp->content),
			' ', width - ft_strlen(tmp->content));
		row[width] = '\0';
		game->worldmap->map[i] = row;
		tmp = tmp->next;
		i++;
	}
	return (TRUE);
}
