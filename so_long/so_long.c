/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 15:49:10 by ddurrand          #+#    #+#             */
/*   Updated: 2022/03/05 14:03:59 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map_and_error_exit(char **map, char *massage)
{
	int	i;

	i = -1;
	if (!map)
		print_error_and_exit(massage);
	while (map[++i])
		free(map[i]);
	free(map);
	print_error_and_exit(massage);
}

void	print_error_and_exit(char *s)
{
	write(1, "Error\n", ft_strlen("Error\n"));
	if (s)
		write(1, s, ft_strlen(s));
	exit(EXIT_FAILURE);
}

char	*ft_strstr(char *haystack, char *needle)
{
	int	i;
	int	j;

	i = 0;
	if (needle[i] == '\0')
		return ((char *)haystack);
	while (haystack[i])
	{
		j = 0;
		while (haystack[i + j] == needle[j])
		{
			if (needle[j + 1] == '\0')
				return ((char *)haystack + i);
			++j;
		}
		++i;
	}
	return (0);
}

char	**get_map(int argc, char **argv)
{
	int		fd;
	char	**map;

	if (argc < 2)
		return (0);
	if (!ft_strstr(argv[1], ".ber"))
		return (0);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (0);
	map = get_map_from_file(fd, argv[1]);
	return (map);
}

int	main(int argc, char **argv)
{
	t_mlx	mlx;
	char	**map;
	int		fd;

	map = get_map(argc, argv);
	if (!map)
		print_error_and_exit("map error");
	mlx_start_init(&mlx, map);
	draw_frame(&mlx);
	mlx_hook(mlx.win, 2, 0, key_hook, &mlx);
	mlx_hook(mlx.win, 17, 0, exit_hook, &mlx);
	mlx_loop(mlx.mlx);
}
