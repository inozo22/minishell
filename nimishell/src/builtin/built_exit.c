/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-mada <bde-mada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 13:05:08 by nimai             #+#    #+#             */
/*   Updated: 2023/08/29 15:16:56 by bde-mada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief check if it's numeric.
 * @author nimai
 * @note ignore the space before the number begins. also fine with boolean
 */
int	is_numeric(char *num)
{
	while (*num == 32)
		num++;
	while (*num)
	{
		if (!ft_isdigit(*num))
			return (0);
		num++;
	}
	return (1);
}

/**
 * @brief doesn't leave from the program, just return.
 * @author nimai
 * @note maybe it's not necessary to have as a function. 
 */
int	error_exit_msg(int ret, char *msg)
{
	ft_printf("exit\n%s\n", msg);
	return (ret);
}

/**
 * @brief to know argv's amount.
 * @author nimai
 * @return how many argvs you have, in int. 
 */
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

/**
 * @brief manage "builtin" exit cmd.
 * @author nimai
 * @param **av "exit", "0"
 * @return if there are more than <cmd + 1 argument>, return to minishell prompt, without execute any function after this.
 * @note 230611nimai: free in the main, so don't have to free memory here.
 */
int	built_exit(char **input, int cmd_num)
{
	int	amount;

	g_return_val = 0;
	amount = av_amount(input);
	if (amount >= 3)
	{
		//230523nimai:when return it, it will not move to next command, but return to minishell prompt
		return (error_exit_msg(1, "minishell: exit: too many arguments"));
	}
	else if (amount > 1 && !is_numeric(input[1]))
	{
		//230523nimai:give you error msg, but exit works. (as working bash)
		ft_printf("minishell: exit: %s: numeric argument required\n", input[1]);
	//230523nimai:will be eliminated
		g_return_val = 255;
	}
	else if (amount == 2)
		g_return_val = ft_atoi(input[1]);
	ft_printf("EXIT!\n");
	if (cmd_num == 0)
		g_return_val = 1;
	return (0);
}
