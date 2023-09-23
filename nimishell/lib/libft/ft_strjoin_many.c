/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_many.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 19:41:45 by bde-mada          #+#    #+#             */
/*   Updated: 2023/09/23 13:58:47 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>
#include <stdio.h>

char	*ft_strjoin_many(int n, char const *s1, ...)
{
	va_list	args;
	char	*tmp;
	char	*str;
	char	*read;

	va_start(args, s1);
	str = ft_strjoin(s1, va_arg(args, char *));
	n--;
	while (--n)
	{
		tmp = str;
		printf("Line: %d p_tmp: %p\n", __LINE__, tmp);
		read = va_arg(args, char *);
		if (!read || !*read)
		{
			printf("Line: %d\n", __LINE__);
			break ;
		}
		str = ft_strjoin(tmp, read);
		free(tmp);
		tmp = NULL;
	}
	printf("Line: %d p_tmp: %p\n", __LINE__, tmp);
	va_end(args);
	return (str);
}

char	*ft_strjoin_array(char **list)
{
	int		i;
	char	*joined;
	char	*tmp;

	i = -1;
	joined = ft_strdup("");
	while (list[++i])
	{
		tmp = joined;
		if (i == 0)
			joined = ft_strjoin(joined, list[i]);
		else
			joined = ft_strjoin_many(3, joined, " ", list[i]);
		free (tmp);
	}
	return (joined);
}

/* int	main(void)
{
	char	*str;
	char	**list;
	int		i;

	i = -1;
	str = ft_strjoin_many(5, "Hola ", "Test ", "prueba ", "hey", "");
	ft_printf("%s\n", str);
	free (str);
	list = ft_split("For lists of detected and suppressed errors", ' ');
	str = ft_strjoin_array(list);
	ft_printf("%s\n", str);
	while (list[++i])
		free(list[i]);
	free(list);
	free(str);
} */
