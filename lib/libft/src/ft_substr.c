/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 11:37:59 by nimai             #+#    #+#             */
/*   Updated: 2023/05/01 11:10:42 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*pmem;
	size_t	i;
	size_t	plen;
	size_t	s_len;

	i = 0;
	s_len = ft_strlen(s);
	if ((long)(s_len - start) < 0)
		plen = 0;
	else if (s_len - start > len)
		plen = len;
	else
		plen = s_len - start;
	pmem = malloc(plen + 1);
	if (pmem == NULL)
		return (NULL);
	while (i < plen && s[i + start])
	{
		pmem[i] = s[i + start];
		i++;
	}
	pmem[i] = 0;
	return (pmem);
}
