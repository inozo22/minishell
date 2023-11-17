/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 09:43:46 by nimai             #+#    #+#             */
/*   Updated: 2023/11/17 09:38:50 by nimai            ###   ########.fr       */
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
char	*get_dest_path_wl_sign(char *cur, char *pwd, char *input, t_data *data)
{
	char	*ret;
	char	*tmp;

	ret = NULL;
	tmp = NULL;
	if (cur)
	{
		if (chdir(cur) == -1)
		{
			data->return_val = 1;
			return (error_built("cd", \
					"failure to move to current directory\n"), NULL);
		}
		ret = ft_strdup(cur);
	}
	else if (!cur)
	{
		if (pwd[ft_strlen(pwd) - 1] != '/')
			tmp = ft_strjoin("/", input);
		else
			tmp = ft_strdup(input);
		ret = ft_strjoin(pwd, tmp);
		ft_printf("%s\n", MSG_CD_CANT_ACCESS);
	}
	return (free (tmp), ret);
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
		data->return_val = 1;
		return (error_notset("cd", envtype), NULL);
	}
	if (chdir(ret) == -1)
	{
		data->return_val = 1;
		return (error_cd(ret), NULL);
	}
	if (!ft_strcmp("OLDPWD", envtype))
		ft_printf("%s\n", ret);
	return (ret);
}
