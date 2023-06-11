/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 13:05:08 by nimai             #+#    #+#             */
/*   Updated: 2023/06/01 16:30:25 by nimai            ###   ########.fr       */
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
 * @note as get out from process, you have to free everything here!!
 */
int	built_exit(t_temp *temp)
{
	int	amount;

	amount = av_amount((char **)temp->argv);
	if (amount == 2)
		exit (0);
	if (!is_numeric(temp->argv[2]))
	{
		//230523nimai:give you error msg, but exit works. (as working bash)
		ft_printf("minishell: exit: %s: numeric argument required\n", temp->argv[2]);
	//230523nimai:will be eliminated
		ft_printf("receive error message, but EXIT!\n");
		exit (1);
	}
	if (amount > 3)
	{
		//230523nimai:when return it, it will not move to next command, but return to minishell prompt
		return (error_exit_msg(1, "minishell: exit: too many arguments"));
	}
	ft_printf("EXIT!\n");
	free (temp);//

//PUT SUPER FREE

	exit (ft_atoi(temp->argv[2]));
	return (0);
}