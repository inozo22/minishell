/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 13:05:08 by nimai             #+#    #+#             */
/*   Updated: 2023/10/10 16:32:26 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief check if it's numeric.
 * @author nimai
 * @note ignore the space before the number begins. also fine with boolean
 * @note also check if it's in long 
 */
int	is_numeric(char *num)
{
	int	i;

	i = 0;
	if (*num == '-' || *num == '+')
	{
		if (*num == '-')
		{
			i = 1;
		}
		num++;
	}
	if (ft_strlen(num) > 19)
		return (0);
	if (ft_strlen(num) == 19 && ((!i && ft_strcmp(num, "9223372036854775807") \
	> 0) || (i && ft_strcmp(num, "9223372036854775808") > 0)))
		return (0);
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
static int	error_exit_msg(void)
{
	ft_putendl_fd("minishell: exit: too many arguments", 2);
	return (1);
}

/**
 * @brief manage "builtin" exit cmd.
 * @author nimai
 * @param **av "exit", "0"
 * @return if there are more than <cmd + 1 argument>, return to minishell
 * prompt, without execute any function after this.
 * @note 230611nimai: free in the main, so don't have to free memory here.
 * @note 230918nimai: add lines to control exit value 
 */
int	built_exit(char **input, t_data *data, int cmd_num)
{
	int	amount;
	int	ret;

	g_return_val = 0;
	amount = av_amount(input);
	if (amount > 1 && !is_numeric(input[1]))
	{
		ft_printf("minishell: exit: %s: numeric argument required\n", input[1]);
		g_return_val = 255;
	}
	else if (amount >= 3)
		return (error_exit_msg());
	else if (amount == 2)
	{
		ret = ft_atoi(input[1]);
		if (ret < 0)
			ret += 256 * (1 + -(ret) / 256);
		ret %= 256;
		if (ret < 0)
			ret *= -1;
		g_return_val = ret;
	}
	if (cmd_num == 0)
		data->exit_status = 1;
	return (ft_printf("EXIT!\n"), 0);
}
