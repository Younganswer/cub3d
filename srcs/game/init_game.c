#include "../../incs/game.h"
#include "../../incs/parse.h"
#include "../../libs/libmlx/incs/mlx.h"

static const char	*g_dir = "NSWE";
static const int	*g_dx = (int []){-1, 1, 0, 0};
static const int	*g_dy = (int []){0, 0, -1, 1};

t_bool			init_game(t_game *game, char *file);
static t_bool	init_mlx(t_game *game);
static t_bool	init_img(t_game *game);
static t_bool	init_player(t_game *game);

t_bool	init_game(t_game *game, char *file)
{
	size_t	i;

	if (parse(game, file) == FALSE || \
		init_mlx(game) == FALSE || \
		init_img(game) == FALSE || \
		init_player(game) == FALSE)
		return (FALSE);
	game->raycast = ft_calloc(sizeof(t_raycast *), SCREEN_WIDTH, "");
	i = 0;
	while (i < SCREEN_WIDTH)
		game->raycast[i++] = ft_calloc(sizeof(t_raycast), 1, "");
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
			&game->img->size_line, &game->img->endian
			);
	return (TRUE);
}

static t_bool	init_player(t_game *game)
{
	int		row;
	int		i;
	char	*col;

	game->player = ft_calloc(sizeof(t_player), 1, "");
	row = -1;
	while (++row < (int)game->worldmap->height)
	{
		i = -1;
		while (++i < 4)
		{
			col = ft_strchr(game->worldmap->map[row], g_dir[i]);
			if (col == NULL)
				continue ;
			game->player->pos = (t_coord){row, col - game->worldmap->map[row]};
			game->player->dir = (t_coord){g_dx[i], g_dy[i]};
			game->player->plane = (t_coord){g_dy[i], -g_dx[i]};
			return (TRUE);
		}
	}
	return (FALSE);
}
