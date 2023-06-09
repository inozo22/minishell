/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr_int.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 11:37:02 by nimai             #+#    #+#             */
/*   Updated: 2023/06/05 14:55:17 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strnstr_int(const char *s1, const char *s2, size_t len)
{
	long	i;
	long	c;
	size_t	s1len;
	size_t	s2len;

	i = 0;
	c = 0;
	s1len = ft_strlen((char *)s1);
	s2len = ft_strlen((char *)s2);
	if (!s2[0])
		return (0);
	if (len < s2len)
		return (0);
	if (len > s1len)
		len = s1len;
	while ((i <= (long)(len - s2len) && (i <= (long)(s1len - s2len))))
	{
		while ((s1[i + c] == s2[c]) && s2[c] && s1[i + c])
			c++;
		if (!s2[c])
			return (i);
		c = 0;
		i++;
	}
	return (0);
}
