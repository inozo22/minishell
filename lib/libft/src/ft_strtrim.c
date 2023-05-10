/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 11:37:42 by nimai             #+#    #+#             */
/*   Updated: 2023/05/01 11:10:38 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	get_first(char *s1, char *set)
{
	int	fst;

	fst = 0;
	while (s1[fst])
	{
		if (!ft_strchr(set, s1[fst]))
			break ;
		fst++;
	}
	return (fst);
}

static int	get_last(char *s1, char *set)
{
	size_t	lst;	

	if (ft_strlen(s1) == 0)
		return (0);
	lst = ft_strlen(s1) - 1;
	while (s1[lst])
	{
		if (!ft_strchr(set, s1[lst]))
			break ;
		lst--;
	}
	return (lst);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		first;
	int		last;
	int		i;

	first = get_first((char *)s1, (char *)set);
	last = get_last((char *)s1, (char *)set);
	if (last - first < 0 || (ft_strlen(s1) == 0))
	{
		str = malloc(1);
		if (str == NULL)
			return (NULL);
		str[0] = '\0';
		return (str);
	}
	str = (char *)malloc(last - first + 2);
	if (str == NULL)
		return (NULL);
	i = -1;
	while (++i < (last - first + 1))
		str[i] = s1[first + i];
	str[i] = '\0';
	return (str);
}
