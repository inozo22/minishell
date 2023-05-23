/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 19:34:52 by nimai             #+#    #+#             */
/*   Updated: 2023/04/26 13:58:56 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	put_char(char c)
{
	ftp_putchar_fd(c, 1);
	return (1);
}

size_t	put_str(char *str)
{
	ftp_putstr_fd(str, 1);
	return (ftp_strlen(str));
}

unsigned long	put_u_nbr(unsigned long nb, unsigned long base, int i)
{
	size_t	len;

	len = 0;
	if (nb >= base)
		len += put_u_nbr(nb / base, base, i);
	if (base == 10)
	{
		ftp_putchar_fd(("0123456789")[nb % base], 1);
		len++;
	}
	else
	{
		if (i == 0)
		{
			ftp_putchar_fd(("0123456789abcdef")[nb % base], 1);
			len++;
		}
		if (i == 1)
		{
			ftp_putchar_fd(("0123456789ABCDEF")[nb % base], 1);
			len++;
		}
	}	
	return (len);
}

int	put_nbr(va_list ap)
{
	int				i;
	unsigned int	len;

	len = 0;
	i = va_arg(ap, int);
	if (i < 0)
	{
		if (i == -2147483648)
		{
			len = put_str("-2147483648");
			return (len);
		}			
		len += put_char('-');
		i *= -1;
	}
	len += put_u_nbr(i, 10, 0);
	return (len);
}

unsigned long	put_pointer(va_list ap)
{
	unsigned long	p;
	unsigned int	len;

	len = 0;
	p = va_arg(ap, unsigned long);
	len += put_str("0x");
	if (!p)
		return (len += put_char('0'));
	else
		len += put_u_nbr(p, 16, 0);
	return (len);
}
