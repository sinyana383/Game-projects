/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_frame.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 13:19:23 by ddurrand          #+#    #+#             */
/*   Updated: 2022/03/03 17:41:56 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	*get_image(t_mlx *mlx, char im, int i, int j)
{
	if (im == '0')
		return (mlx->im.space);
	if (im == '1')
	{
		if (j == 0 || j == mlx->game.map_size[0] - 1)
			return (mlx->im.wall_side);
		if (i == 0)
			return (mlx->im.wall_up);
		if (i == mlx->game.map_size[1] - 1)
			return (mlx->im.wall_down);
		else
			return (mlx->im.wall_free);
	}
	if (im == 'P')
		return (mlx->im.player_now);
	if (im == 'C')
		return (mlx->im.collect);
	if (im == 'E')
		return (mlx->im.exit);
	return (0);
}

void	draw_frame(t_mlx *mlx)
{
	char	**map;
	int		i;
	int		j;
	void	*im;

	map = mlx->game.map;
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			im = get_image(mlx, map[i][j], i, j);
			if (!im)
				free_map_and_error_exit(mlx->game.map, "map error");
			mlx_put_image_to_window(mlx->mlx, mlx->win, im, \
			mlx->im.width * j, mlx->im.hight * i);
		}
	}
}
