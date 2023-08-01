/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:02:13 by ddurrand          #+#    #+#             */
/*   Updated: 2022/03/03 17:28:58 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	exit_hook(t_mlx *mlx)
{
	int		i;
	char	**map;

	map = mlx->game.map;
	i = -1;
	while (map[++i])
		free(map[i]);
	free(map);
	exit(EXIT_SUCCESS);
}
