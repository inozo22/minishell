/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 09:50:16 by nimai             #+#    #+#             */
/*   Updated: 2023/05/29 13:53:21 by nimai            ###   ########.fr       */
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
	char		**tmp_env;
	int			i;
	int			len;

	(void)av;
	tmp_env = fake_env();
	if (!tmp_env)
	{
		return (printf("ERROR: Line: %d\n", __LINE__), 0);
	}
	i = 0;
	len = av_amount(tmp_env);
	while (i < len)
	{
		ft_printf("%s\n", tmp_env[i]);
	//	free (tmp_env[i]);
	//	system ("leaks minishell");
		i++;
	}
	//ptr_free((void **)tmp_env);
	//	free (tmp_env[i]);
	//free (tmp_env);
    return (0);
}

/**
 * BEHAVIOUR IN BASH
 * when execute env, the list is not ordered 
 * 
 * 
 * MEMORY LEAKS
 * 230526nimai: When I try free it, receive errors say that I'm trying free memory which is not allocated.
 * But yes, allocated.
 * 
 */