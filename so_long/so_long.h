/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 15:49:45 by ddurrand          #+#    #+#             */
/*   Updated: 2022/03/03 17:29:04 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <stdio.h>

typedef struct s_game
{
	char	**map;
	int		map_size[2];
	int		player_pos[2];
	int		score_all;
	int		score_cur;
	int		steps;
	int		game_over;
}	t_game;
typedef struct s_image
{
	int		width;
	int		hight;
	void	*wall_free;
	void	*wall_up;
	void	*wall_side;
	void	*wall_down;
	void	*player_now;
	void	*player_free_right;
	void	*player_free_left;
	void	*player_exit_right;
	void	*player_exit_left;
	void	*space;
	void	*exit;
	void	*collect;
}	t_image;
typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	int		win_width;
	int		win_hight;
	t_image	im;
	t_game	game;
}	t_mlx;
int		check_map_and_set_map_elems( \
t_game *game_elems, char **map, int *x, int *y);
void	draw_frame(t_mlx *mlx);
int		exit_hook(t_mlx *mlx);
int		key_hook(int keycode, t_mlx *mlx);
void	print_error_and_exit(char *s);
int		mlx_start_init(t_mlx *mlx, char **map);
char	**get_map_from_file(int fd, char *mapfile);
char	*ft_strchr(const char *s, int c);
int		ft_printf(const char *format, ...);
int		ft_strlen(char *s);
char	*ft_strchr(const char *s, int c);
void	free_map_and_error_exit(char **map, char *massage);
#endif