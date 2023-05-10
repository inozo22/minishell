/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 19:35:14 by nimai             #+#    #+#             */
/*   Updated: 2023/05/08 10:03:21 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdarg.h>

int				ft_printf(char const *str, ...);
size_t			put_char(char c);
int				put_nbr(va_list ap);
unsigned long	put_pointer(va_list ap);
size_t			put_str(char *str);
unsigned long	put_u_nbr(unsigned long nb, unsigned long base, int i);
void			ftp_putchar_fd(char c, int fd);
void			ftp_putstr_fd(char *s, int fd);
size_t			ftp_strlen(const char *s);

#endif
