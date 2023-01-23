#include "../../incs/game.h"
#include "../../incs/parse.h"
#include "../../libs/libmlx/incs/mlx.h"

t_bool			init_game(t_game *game, char *file);
static t_bool	init_mlx(t_game *game);
static t_bool	init_img(t_game *game);
static t_bool	init_player(t_game *game);

t_bool	init_game(t_game *game, char *file)
{
	if (parse(game, file) == FALSE || \
		init_mlx(game) == FALSE || \
		init_img(game) == FALSE || \
		init_player(game) == FALSE)
		return (FALSE);
	return (TRUE);
}

static t_bool	init_mlx(t_game *game)
{
	game->mlx = ft_calloc(sizeof(t_mlx), 1, "");
	game->mlx->mlx = mlx_init();
	if (game->mlx->mlx == NULL)
		return (FALSE);
	game->mlx->window = \
		mlx_new_window(game->mlx->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D");
	if (game->mlx->window == NULL)
		return (FALSE);
	return (TRUE);
}

static t_bool	init_img(t_game *game)
{
	game->img = ft_calloc(sizeof(t_img), 1, "");
	game->img->img_to_render = mlx_new_image(
			game->mlx->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (game->img->img_to_render == NULL)
		return (FALSE);
	game->img->img_buffer = mlx_new_image(
			game->mlx->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (game->img->img_buffer == NULL)
		return (FALSE);
	game->img->data = (int *) mlx_get_data_addr(
			game->img->img_to_render, &game->img->bits_per_pixel,
			&game->img->size_line, &game->img->endian);
	return (TRUE);
}

static t_bool	init_player(t_game *game)
{
	const char	*dir = "NSWE";
	const int	*dx = (int []){-1, 1, 0, 0};
	const int	*dy = (int []){0, 0, -1, 1};
	t_list		*tmp;
	size_t		i;

	game->player = ft_calloc(sizeof(t_player), 1, "");
	tmp = game->map;
	while (tmp != NULL)
	{
		i = 0;
		while (i < 4)
		{
			if (ft_strchr(tmp->content, dir[i++]) == NULL)
				continue ;
			game->player->pos = (t_coord){ft_lstindex(game->map, tmp->content),
				ft_strchr(tmp->content, dir[i - 1]) - (char *) tmp->content};
			game->player->dir = (t_coord){dx[i - 1], dy[i - 1]};
			game->player->plane = (t_coord){0, 0.66};
			return (TRUE);
		}
		tmp = tmp->next;
	}
	return (FALSE);
}
