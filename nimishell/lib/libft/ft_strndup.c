/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:28:31 by nimai             #+#    #+#             */
/*   Updated: 2023/08/11 11:28:48 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "libft.h"

char	*ft_strndup(const char *s1, int len)
{
	char	*dest;

	dest = (char *)ft_calloc(len + 1, sizeof(char));
	if (!dest)
	{
		return (NULL);
		errno = 12;
	}
	dest[len] = '\0';
	len--;
	while (len >= 0)
	{
		dest[len] = s1[len];
		len--;
	}
	return (dest);
}
