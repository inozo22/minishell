/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:54:13 by nimai             #+#    #+#             */
/*   Updated: 2023/05/23 18:37:33 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief look for flag, doesn't matter how many n's has
 * @author nimai
 * @return if it's flag, returns 1, if it's included flag some number more than 1, otherwise 0. Hope anyone put more than 2147483647 ns
 */
int	is_flag(char *str)
{
	int	ret;

	ret = 0;
	if (str[ret] != '-' || str[ret + 1] != 'n')
		return (0);
	ret++;
	while (str[++ret])
	{
		if (str[ret] != 'n')
			break ;
	}
	if (str[ret] != '\0')
	{
		return (ret);
	}
	return (1);
}

/**
 * @brief manage "builtin" echo cmd.
 * @author nimai
 * @param **av "echo", "-n", "str (could be in large numbers as 10,000 byte)"
 * @return if there are more than <cmd + 1 argument>, return to minishell prompt, without execute any function after this.
 */
int	built_echo(char **av)
{
	int	i;
	int	flag[2];
	int	amount;

	amount = av_amount(av);
	i = 2;//230523nimai: start from 2 to look for flags.
	flag[0] = is_flag(av[i]);
	if (flag[0] == 1)
		i++;
	while (i < amount)
	{
		flag[1] = is_flag(av[i]);
		if (flag[1] > 1 || flag[1] == 0)
			ft_printf("%s", av[i]);
		if (i < amount - 1 && flag[1] != 1)//230523nimai: has to skip when flag[1]==1
			ft_printf(" ");
		i++;
	}
	if (flag[0] != 1)
		ft_printf("\n");
	return (0);
}

/**
 * 230523nimai: Working with flag, without flag, multipul flags, but doesn't work flag strange suche as "-naaa"
 * 
 * 
 * 	printf("Line: %d\n", __LINE__);
 * 	printf("str[ret]: %c\n", str[ret]);
 */