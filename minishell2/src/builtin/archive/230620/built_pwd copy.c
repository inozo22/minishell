/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:11:36 by nimai             #+#    #+#             */
/*   Updated: 2023/06/20 13:32:42 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief old pwd function
 * @author nimai
 * @param **av "pwd"
 * @return if there are sth after cmd, ignore and execute it normally. Don't manage any flags.
 * @note getcwd allocate mamory when it's executed, so it should be freed
 */
/* int	built_pwd(t_data *data)
{
	char	*mycwd;

	(void)data;
	mycwd = getcwd(NULL, 0);
	ft_printf("%s\n", mycwd);
	free (mycwd);
	return (0);
	//230523nimai: should be managed the flags? (at least give some message?)
}
 */

/**
 * @author nimai
 * @param "pwd"
 * @return if there are sth after cmd, ignore and execute it normally. Don't manage any flags.
 * @note obtain pwd from static pwd in built_cd. So you can also obtain after unset PWD
 */
int	built_pwd(t_data *data)
{
	built_cd(NULL, data);
	return (0);
/* 	int		i;
	char	*mycwd;

	mycwd = NULL;
	i = -1;
	while (data->env[++i])
	{
		if (ft_strncmp(data->env[i], "PWD=", 4) == 0)
		{
			ft_printf("%s\n", (data->env[i] + 4));
			return (0);
		}
	}
	mycwd = getcwd(NULL, 0);
	if (!mycwd)
		return (1);
	ft_printf("%s\n", mycwd);
	free (mycwd);
	return (0); */
}
