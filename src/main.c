/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 12:52:29 by nimai             #+#    #+#             */
/*   Updated: 2023/05/23 13:21:31 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av)
{
	if (ac < 2)
	{
		return (0);
	}
	if (ft_strncmp(av[1], "exit", 4) == 0)
	{
		printf("I got exit\n");
		built_exit(av);
	}
	return (0);
}

