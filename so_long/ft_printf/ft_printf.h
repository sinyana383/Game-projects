/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 15:44:08 by ddurrand          #+#    #+#             */
/*   Updated: 2022/03/03 17:42:17 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

int		ft_printf(const char *format, ...);
char	*ft_strchr(const char *s, int c);
int		ft_strlen(char *s);
int		print_pointer(void *p);
int		print_decimal(int number);
int		print_unsigned_int(int num);
int		print_hexadecimal(int num, char x);
#endif