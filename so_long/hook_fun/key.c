/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 14:17:34 by ddurrand          #+#    #+#             */
/*   Updated: 2022/03/05 13:15:55 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	next_cell(t_mlx *mlx, int y_move, int x_move)
{
	if (mlx->game.map[y_move][x_move] == 'E')
	{
		if (mlx->im.player_now == mlx->im.player_free_left || \
		mlx->im.player_now == mlx->im.player_exit_left)
			mlx->im.player_now = mlx->im.player_exit_left;
		else
			mlx->im.player_now = mlx->im.player_exit_right;
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->im.player_now, \
		mlx->im.width * (x_move), mlx->im.hight * (y_move));
		if (mlx->game.score_cur >= mlx->game.score_all)
			mlx->game.game_over = 1;
	}
	else
	{
		if (mlx->game.map[y_move][x_move] == 'C')
			mlx->game.score_cur += 1;
		mlx->game.map[y_move][x_move] = '0';
		if (mlx->im.player_now == mlx->im.player_exit_left)
			mlx->im.player_now = mlx->im.player_free_left;
		else if (mlx->im.player_now == mlx->im.player_exit_right)
			mlx->im.player_now = mlx->im.player_free_right;
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->im.player_now, \
		mlx->im.width * (x_move), mlx->im.hight * (y_move));
	}
}

int	move(t_mlx *mlx, int i, int j)
{
	int		x;
	int		y;

	x = mlx->game.player_pos[0];
	y = mlx->game.player_pos[1];
	if (mlx->game.map[y + i][x + j] == '1')
		return (0);
	if (mlx->game.map[y][x] == 'E')
	{
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->im.exit, \
		mlx->im.width * x, mlx->im.hight * y);
	}
	else
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->im.space, \
		mlx->im.width * x, mlx->im.hight * y);
	next_cell(mlx, y + i, x + j);
	mlx->game.player_pos[0] = x + j;
	mlx->game.player_pos[1] = y + i;
	mlx->game.steps += 1;
	ft_printf("%d\n", mlx->game.steps);
	return (1);
}

int	before_move(t_mlx *mlx, int *x, int *y, int keycode)
{
	if (mlx->game.game_over)
	{
		if (keycode == 53)
			exit_hook(mlx);
		return (-1);
	}
	*x = mlx->game.player_pos[0];
	*y = mlx->game.player_pos[1];
	return (1);
}

int	key_hook(int keycode, t_mlx *mlx)
{
	int	x;
	int	y;

	if (before_move(mlx, &x, &y, keycode) < 0)
		return (0);
	if (keycode == 0 && mlx->game.map[y + 0][x - 1] != '1')
	{
		mlx->im.player_now = mlx->im.player_free_left;
		move(mlx, 0, -1);
	}
	else if (keycode == 1)
		move(mlx, 1, 0);
	else if (keycode == 2 && mlx->game.map[y + 0][x + 1] != '1')
	{
		mlx->im.player_now = mlx->im.player_free_right;
		move(mlx, 0, 1);
	}
	else if (keycode == 13)
		move(mlx, -1, 0);
	if (keycode == 53)
		exit_hook(mlx);
	return (0);
}
