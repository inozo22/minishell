/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 09:43:46 by nimai             #+#    #+#             */
/*   Updated: 2023/09/08 16:01:36 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief manage "builtin" cd cmd.
 * @author nimai
 * @param **av "cd", "path".
 * @return 
 * @note you will get OLDPWD
 */
char	*get_dest_path_wl_sign(t_data *data, char *cur, char *pwd)
{
	char	*ret;

	ret = NULL;
	(void)data;
	if (cur) //move to where you are, you will get OLDPWD
	{
		if (chdir(cur) == -1)
		{
			g_return_val = 1;
			return (error_built("cd", \
					"failure to move to current directory\n"), NULL);
		}
		ret = ft_strdup(cur);
	}
	else if (!cur) //move to where you are, but if it's not exist
	{
		// I think I should put input instead of "./" because could be any string
		ret = ft_strjoin(pwd, "./");
		ft_printf("cd: error retrieving current directory: getcwd: \
				cannot access parent directories: No such file or directory"); //temporary error control
	}
	return (ret);
}

/**
 * @brief manage "builtin" cd cmd.
 * @author nimai
 * @param envtype HOME or OLDPWD
 * @return 
 * @note if there is no value, receive "??? not set" message
 */
char	*get_dest_path_env(t_data *data, char *envtype)
{
	char	*ret;

	ret = get_env(data->env, envtype);
	if (!ret)
	{
		g_return_val = 1;
		return (error_notset("cd", envtype), NULL);
	}
	if (chdir(ret) == -1)
	{
		g_return_val = 1;
		return (error_built("cd", "failed chdir"), NULL);
	}
	if (!ft_strcmp("OLDPWD", envtype))
		ft_printf("%s\n", ret);
	return (ret);
}
