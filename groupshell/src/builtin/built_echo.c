/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:54:13 by nimai             #+#    #+#             */
/*   Updated: 2023/06/20 17:25:12 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief look for flag, doesn't matter how many n's has
 * @author nimai
 * @return if it's flag, returns 1, if it's included flag some number more than 1, otherwise 0.
 * Hope anyone put more than 2147483647 ns
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
 * @brief OLD ONE manage "builtin" echo cmd.
 * @author nimai
 * @param **av "echo", "-n", "str (could be in large numbers as 10,000 byte)"
 * @param flag[0] the first flag check
 * @param flag[1] from second flag
 * @return anyway print what you put after cmd, if there is no argument put "\n".
 */
/* int	built_echo(char **input)
{
	int	i;
	int	flag[2];
	int	amount;

	amount = av_amount(input);
	if (amount < 2)
		return (ft_printf("\n"), 0);
	i = 1;//230523nimai: start from 2 to look for flags.
	flag[0] = is_flag(input[i]);
	if (flag[0] == 1)
		i++;
	while (i < amount)
	{
		flag[1] = is_flag(input[i]);
		if (flag[1] > 1 || flag[1] == 0 || (flag[1] == 1 && flag[0] == 1))
			ft_printf(input[i]);
		//230523nimai: has to skip when flag[1]==1
		if (i < amount - 1 && flag[1] != 1)
			ft_printf(" ");
		i++;
	}
	if (flag[0] != 1)
		ft_printf("\n");
	return (0);
} */

/**
 * @brief manage "builtin" echo cmd.
 * @author nimai
 * @param **av "echo", "-n", "str (could be in large numbers as 10,000 byte)"
 * @param flag[0] the first flag check, for '\n'
 * @param flag[1] from second flag, to check if it should be printed
 * @return anyway print what you put after cmd, if there is no argument put "\n".
 */
int	built_echo(char **input)
{
	int	i;
	int	flag[2];
	int	amount;

	amount = av_amount(input);
	ft_bzero(flag, 2 * sizeof(int));
	if (amount < 2)
		return (ft_printf("\n"), 0);
	i = 1;//230523nimai: start from 2 to look for flags.
	flag[0] = is_flag(input[i]);
	if (flag[0] == 1 && input[i++])
		flag[1] = 1;
	while (i < amount)
	{
		if (is_flag(input[i]) != 1)
			flag[1] = 0;
		if (flag[1] == 0)
			ft_printf(input[i]);
		if (i < amount - 1 && flag[1] == 0)
			ft_printf(" ");
		i++;
	}
	if (flag[0] != 1)
		ft_printf("\n");
	return (0);
}

/**
 * 230523nimai: Working with flag, without flag, multipul flags. 
 * Also manage strange flag such as "-naann" and without arguments.
 * 
 * 
 * 	printf("Line: %d\n", __LINE__);
 * 	printf("str[ret]: %c\n", str[ret]);
 * 
 * 230614nimai: is there possibility to failure command echo??
 */
