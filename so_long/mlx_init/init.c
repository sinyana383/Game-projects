/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 15:58:09 by ddurrand          #+#    #+#             */
/*   Updated: 2022/03/05 13:33:43 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	mlx_init_game(t_game *game, char **map)
{
	game->map = map;
	game->player_pos[0] = -1;
	game->player_pos[1] = -1;
	game->map_size[0] = -1;
	game->map_size[1] = -1;
	game->score_all = 0;
	game->score_cur = 0;
	game->steps = 0;
	game->game_over = 0;
}

char	*check_ims(t_image *im)
{
	if (!(im->wall_up && im->wall_down && im->wall_side && im->wall_free))
		return ("wall image");
	if (!(im->player_exit_left && im->player_exit_right \
	&& im->player_free_left && im->player_free_right && im->player_now))
		return ("player image");
	if (!(im->space && im->exit && im->collect))
		return ("0 or E or C image");
	return (0);
}

void	wall_init(t_mlx *mlx)
{
	mlx->im.wall_free = mlx_xpm_file_to_image \
	(mlx->mlx, "texturs_32/wall_free.xpm", &mlx->im.width, &mlx->im.hight);
	mlx->im.wall_up = mlx_xpm_file_to_image \
	(mlx->mlx, "texturs_32/wall_up.xpm", &mlx->im.width, &mlx->im.hight);
	mlx->im.wall_down = mlx_xpm_file_to_image \
	(mlx->mlx, "texturs_32/wall_down.xpm", &mlx->im.width, &mlx->im.hight);
	mlx->im.wall_side = mlx_xpm_file_to_image \
	(mlx->mlx, "texturs_32/wall_side.xpm", &mlx->im.width, &mlx->im.hight);
}

char	*mlx_init_im(t_mlx *mlx)
{
	mlx->im.width = 32;
	mlx->im.hight = 32;
	wall_init(mlx);
	mlx->im.space = mlx_xpm_file_to_image \
	(mlx->mlx, "texturs_32/free_space.xpm", &mlx->im.width, &mlx->im.hight);
	mlx->im.exit = mlx_xpm_file_to_image \
	(mlx->mlx, "texturs_32/exit.xpm", &mlx->im.width, &mlx->im.hight);
	mlx->im.player_free_right = mlx_xpm_file_to_image(mlx->mlx, \
	"texturs_32/player/player_free_right.xpm", &mlx->im.width, &mlx->im.hight);
	mlx->im.player_free_left = mlx_xpm_file_to_image(mlx->mlx, \
	"texturs_32/player/player_free_left.xpm", &mlx->im.width, &mlx->im.hight);
	mlx->im.player_now = mlx->im.player_free_right;
	mlx->im.player_exit_right = mlx_xpm_file_to_image(mlx->mlx, \
	"texturs_32/player/player_exit_right.xpm", &mlx->im.width, &mlx->im.hight);
	mlx->im.player_exit_left = mlx_xpm_file_to_image(mlx->mlx, \
	"texturs_32/player/player_exit_left.xpm", &mlx->im.width, &mlx->im.hight);
	mlx->im.collect = mlx_xpm_file_to_image(mlx->mlx, \
	"texturs_32/winter_bird_free.xpm", &mlx->im.width, &mlx->im.hight);
	return (check_ims(&(mlx->im)));
}

int	mlx_start_init(t_mlx *mlx, char **map)
{
	int		check;
	char	*error_massage;

	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		free_map_and_error_exit(mlx->game.map, "mlx init failed");
	mlx_init_game(&(mlx->game), map);
	error_massage = mlx_init_im(mlx);
	if (error_massage)
		free_map_and_error_exit(mlx->game.map, error_massage);
	check = check_map_and_set_map_elems(&(mlx->game), map, \
	&(mlx->game.map_size[0]), &(mlx->game.map_size[1]));
	if (check < 0)
		free_map_and_error_exit(mlx->game.map, "map_error");
	mlx->win_width = mlx->game.map_size[0] * mlx->im.width;
	mlx->win_hight = mlx->game.map_size[1] * mlx->im.hight;
	mlx->win = mlx_new_window \
	(mlx->mlx, mlx->win_width, mlx->win_hight, "./so_long");
	if (!mlx->win)
		free_map_and_error_exit(mlx->game.map, "create win failed");
	return (1);
}
