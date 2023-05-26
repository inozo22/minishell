/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 09:50:16 by nimai             #+#    #+#             */
/*   Updated: 2023/05/26 13:33:00 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief temporary error management
 * @author nimai
 * @note when decided error management, merge it.
 */
void	error_env(char *cmd)
{
	ft_printf("minishell: env: %s: Dunno\n", cmd);
}

/**
 * @brief manage "builtin" env cmd.
 * @author nimai
 * @param **av "env", no flags, no arguments
 * @return 
 */
int	built_env(char **av)
{
	t_export	*list;
	char		**tmp_env;

	if (av_amount(av) == 2)
	{
		tmp_env = fake_env();
		if (!tmp_env)
		{
			return (printf("ERROR: Line: %d\n", __LINE__), 0);
		}
		list = (t_export *)malloc(sizeof(t_export));
		if (!list)
			return (0);
		list = fill_list(tmp_env, list);
		output_env(list, av_amount(tmp_env), FLAGENV);
	}

    return 0;
}

/**
 * BEHAVIOUR IN BASH
 * when execute env, the list is not ordered 
 * 
 * 
 */