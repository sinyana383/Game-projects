/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_get_size.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 13:19:23 by ddurrand          #+#    #+#             */
/*   Updated: 2022/03/05 13:40:33 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	check_for_wall(char **map, int i, int j)
{
	if (i == 0 && map[i][j] != '1')
		return (-1);
	if (!map[i + 1] && map[i][j] != '1')
		return (-1);
	if (j == 0 && map[i][j] != '1')
		return (-1);
	if (!map[i][j + 1] && map[i][j] != '1')
		return (-1);
	return (1);
}

int	check_elems(char elem, t_game *game_elems, int *exit)
{
	if (elem == 'C')
		game_elems->score_all += 1;
	else if (elem == 'E')
		*exit = 1;
	else if (!ft_strchr("01CEP", elem))
		return (-1);
	return (1);
}

void	player_pos(t_game *game_elems, char **map, int *x, int *y)
{
	if (game_elems->player_pos[0] > -1 && game_elems->player_pos[1] > -1)
		map[*y][*x] = '0';
	else
	{
		game_elems->player_pos[0] = *x;
		game_elems->player_pos[1] = *y;
	}
}

int	check_map_and_set_map_elems(t_game *game_elems, char **map, int *x, int *y)
{
	int	check_for_exit;

	check_for_exit = 0;
	if (!map)
		return (-1);
	while (map[++(*y)])
	{
		*x = -1;
		while (map[*y][++(*x)])
		{
			if (check_for_wall(map, *y, *x) < 0 \
			|| check_elems(map[*y][*x], game_elems, &check_for_exit) < 0)
				return (-1);
			else if (map[*y][*x] == 'P')
				player_pos(game_elems, map, x, y);
		}
	}
	if (check_for_exit && game_elems->player_pos[0] >= 0 \
	&& game_elems->player_pos[1] >= 0 && game_elems->score_all > 0)
		return (1);
	return (-1);
}
