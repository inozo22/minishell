/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 13:38:55 by nimai             #+#    #+#             */
/*   Updated: 2023/06/02 16:40:42 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ftp_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ftp_putstr_fd(char *s, int fd)
{
	write(fd, s, ftp_strlen(s));
}

size_t	ftp_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}
