/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 11:31:05 by ddurrand          #+#    #+#             */
/*   Updated: 2022/03/03 13:22:08 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# define BUFFER_SIZE 32

int		ft_strlen(char *s);
int		get_next_line(int fd, char **line);
char	*ft_strjoin(char *res, char *buf, int *rl);
int		write_remainder(char *buf, char **rem);
char	*ft_substr(char *s, int start, int len);
int		set_var_and_malloc(int *size, int *fd, char ***res, char *mapfile);
#endif