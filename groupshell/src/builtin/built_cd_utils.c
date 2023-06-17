/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 09:43:46 by nimai             #+#    #+#             */
/*   Updated: 2023/06/17 10:39:01 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_dest_path_wl_sign(t_data *data, char *cur)
{
	char	*ret;

	ret = NULL;
	(void)data;
	if (cur)//move to where you are, you will get OLDPWD
	{
		if (chdir(cur) == -1)
			return (error_built("cd", "failuer to move to current directory\n"), NULL);//
		ret = ft_strdup(cur);
	}
	else if (!cur)//move to where you are, but if it's not exist
	{
		ret = ft_strjoin(getenv("PWD"), "./");
		ft_printf("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory");//temporary error control
	}
	return (ret);
}

char	*get_dest_path_env(t_data *data, char *envtype)
{
	char	*ret;

	ret = get_env(data->env, envtype);
	if (!ret)
		return (error_notset("cd", envtype), NULL);//INT 帰ってるところ、無理にNULLで戻してる。要修正
	if (chdir(ret) == -1)
		return (error_built("cd", "failed chdir"), NULL);
	return (ret);
}
