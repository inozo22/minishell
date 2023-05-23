/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 13:05:08 by nimai             #+#    #+#             */
/*   Updated: 2023/05/23 13:32:58 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_exit_msg(char *msg)
{
	

}

int	av_amount(char **strs)
{
	int	ret;

	ret = 0;
	while (strs[ret])
	{
		ret++;
	}
	return (ret);
}

int	built_exit(char **av)
{
	int	amount;

	amount = av_amount(av);
	printf("amount is %d\n", amount);
	if (amount == 2)
		exit(0);
	else if (amount > 3)
	{
		return (error_exit_msg("minishell: exit: too many arguments\n"));
	}
	else
	{
		
	}

	return (0);
}
