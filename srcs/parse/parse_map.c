#include "../../incs/parse.h"
#include <stdlib.h>

t_bool			parse_map(t_game *game, int fd);
static t_bool	read_map(t_worldmap *worldmap, t_list **tmp_map, int fd);
static t_bool	list_to_string_arr(t_worldmap *worldmap, t_list *tmp_map);

t_bool	parse_map(t_game *game, int fd)
{
	t_bool	ret;
	t_list	*tmp_map;

	ret = FALSE;
	tmp_map = NULL;
	game->worldmap = ft_calloc(sizeof(t_worldmap), 1, "");
	if (read_map(game->worldmap, &tmp_map, fd) && \
		list_to_string_arr(game->worldmap, tmp_map))
		ret = TRUE;
	ft_lstclear(&tmp_map, free);
	return (ret);
}

static t_bool	read_map(t_worldmap *worldmap, t_list **tmp_map, int fd)
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
		ft_lstadd_back(tmp_map, ft_lstnew(row));
		if (worldmap->width < ft_strlen(row))
			worldmap->width = ft_strlen(row);
		free(line);
		worldmap->height++;
	}
	return (TRUE);
}

static t_bool	list_to_string_arr(t_worldmap *worldmap, t_list *tmp_map)
{
	char	*row;
	size_t	i;

	worldmap->map = ft_calloc(sizeof(char *), worldmap->height, "");
	i = 0;
	while (tmp_map != NULL)
	{
		row = ft_calloc(sizeof(char), worldmap->width + 1, "");
		ft_strlcpy(row, tmp_map->content, ft_strlen(tmp_map->content) + 1);
		ft_memset(row + ft_strlen(tmp_map->content),
			' ', worldmap->width - ft_strlen(tmp_map->content));
		row[worldmap->width] = '\0';
		worldmap->map[i] = row;
		tmp_map = tmp_map->next;
		i++;
	}
	return (TRUE);
}
