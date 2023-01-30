#include "../../incs/parse.h"

int *const	g_dx = (int []){-1, 0, 1, 0};
int *const	g_dy = (int []){0, 1, 0, -1};

t_bool			validate_map(t_game *game);
static t_bool	has_non_allowed_char(t_game *game);
static t_bool	map_is_closed(t_game *game);
static t_bool	dfs(t_game *game, size_t x, size_t y, char **const visited);

t_bool	validate_map(t_game *game)
{
	return (has_non_allowed_char(game) && \
		map_is_closed(game)
	);
}

static t_bool	has_non_allowed_char(t_game *game)
{
	t_worldmap *const	worldmap = game->worldmap;
	size_t				i;
	size_t				j;

	i = 0;
	while (i < worldmap->height)
	{
		j = 0;
		while (j < worldmap->width)
		{
			if (ft_strchr("01NSEW ", worldmap->map[i][j]) == NULL)
			{
				game->err = NON_ALLOWED_CHAR_ERR;
				return (FALSE);
			}
			j++;
		}
		i++;
	}
	return (TRUE);
}

static t_bool	map_is_closed(t_game *game)
{
	char **const	visited
		= ft_calloc(sizeof(char *), game->worldmap->height + 1, "");
	size_t			i;

	i = 0;
	while (i < game->worldmap->height)
		visited[i++] = ft_calloc(sizeof(char), game->worldmap->width, "");
	if (dfs(game, game->player->pos.x, game->player->pos.y, visited) == FALSE)
		game->err = MAP_BOARDER_ERR;
	del_string(visited);
	return (game->err == 0);
}

static t_bool	dfs(t_game *game, size_t x, size_t y, char **const visited)
{
	size_t	i;

	visited[x][y] = TRUE;
	if (x == 0 || x == game->worldmap->height - 1 || \
		y == 0 || y == game->worldmap->width - 1)
		return (FALSE);
	i = 0;
	while (i < 4)
	{
		if (game->worldmap->map[x + g_dx[i]][y + g_dy[i]] == ' ')
			return (FALSE);
		if (game->worldmap->map[x + g_dx[i]][y + g_dy[i]] == '0' && \
			visited[x + g_dx[i]][y + g_dy[i]] == FALSE)
		{
			if (dfs(game, x + g_dx[i], y + g_dy[i], visited) == FALSE)
				return (FALSE);
		}
		i++;
	}
	return (TRUE);
}
