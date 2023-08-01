/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 12:22:31 by nimai             #+#    #+#             */
/*   Updated: 2023/08/01 13:05:03 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_list
{
	char			*content;
	int				type;
	int				cmd_pos;
	struct s_list	*next;
}			t_list;

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}


int	main(int ac, char **av)
{
	char	*str;
	char	*str1;
	char	*str2;
	int i = 0;
    t_list  list;

	str = av[1];
	str1 = av[2];
	str2 = av[3];

    // list->content = malloc(4);
    // printf("Imhere");
    // if (!list->content)
    //     return (1);
    list.content = av[1];
    printf("list->content: %p\n", list.content);
    printf("length: %lu\n", strlen(list.content));
    printf("length: %lu\n", ft_strlen(list.content));

	printf("str: %s\n", str);
	printf("str1: %s\n", str1);
	printf("str2: %s\n", str2);

	while (i < ac)
	{
		printf("av[%d]: %s\n", i, av[i]);
		i++;
	}
 //   printf("list->content: %s", list->content);
	return (0);
}
