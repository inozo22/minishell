/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 18:40:39 by nimai             #+#    #+#             */
/*   Updated: 2023/11/15 15:59:45 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief temporary error management
 * @author nimai
 * @note when decided error management, merge it.
 */
void	error_cd(char *cmd)
{
	// g_return_val = 1;
	ft_printf("minishell: cd: %s: No such file or directory\n", cmd);
}

/**
 * @brief obtain destination path
 * @author nimai
 */
char	*get_dest_path(char *dest, t_data *data)
{
	char	*ret;
	char	*cur;

	if (chdir(dest) == -1)
	{
		data->return_val = 1;
		ft_printf("return: %d\n", data->return_val);

		return (/* data->return_val = 1,  */error_cd(dest), NULL);
	}
		// return (g_return_val = 1, error_cd(dest), NULL);
	cur = getcwd(NULL, 0);
	ret = ft_strdup(dest);
	if (ft_strlen(cur) > ft_strlen(ret) && ft_strncmp("..", ret, 2) != 0)
	{
		return (path_modify(cur, ret));
	}
	else if (ft_strlen(cur) <= ft_strlen(ret))
	{
		if (ret[ft_strlen(ret) - 1] == '/')
			return (path_modify(cur, ret));
		return (free (cur), ret);
	}
	else if (!ft_strcmp("//", ret))
		return (free (cur), ret);
	return (free (ret), cur);
}

/**
 * @note to fill static pwd in cd function, 
 * if there is no PWD in env, obtain by getcwd.
 */
void	init_pwd_home(char **pwd, char **home, char **env)
{
	int		i;
	int		j;

	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "PWD=", 4))
			*pwd = ft_strdup(env[i] + 4);
		else if (!ft_strncmp(env[i], "HOME=", 5))
			*home = ft_strdup(env[i] + 5);
	}
	if (!*pwd)
		*pwd = getcwd(NULL, 0);
	if (!*home)
	{
		i = -1;
		j = 0;
		while ((*pwd)[++i] && j < 3)
		{
			if ((*pwd)[i] == '/')
				j++;
		}
		*home = ft_substr(*pwd, 0, i - 1);
	}
}

/**
 * @param flag 99 to free all
 * @param flag 0 to function cd normal
 * @param flag 1 to function pwd
 * @param flag 2 for '~', to send char * to expand
 * @param flag 3 to obtain string pwd
 * @param flag 4 to edit pwd
 * 
 * 
 */
char	*obtain_pwd_home(t_data *data, int flag)
{
	static char	*pwd = NULL;
	static char	*home = NULL;
	char		*tmp;

	if (flag == 99)
		return (my_free(pwd), my_free(home), NULL);
	//data->return_val = 0;
	// g_return_val = 0;
	if (!pwd || !home)
		init_pwd_home(&pwd, &home, data->env);
	if (flag == 1)
		return (ft_printf("%s\n", pwd), NULL);
	if (flag == 2)
		return (ft_strdup(home));
	if (flag == 3)
		return (ft_strdup(pwd));
	if (flag == 4)
	{
		tmp = pwd;
		pwd = get_env(data->env, "PWD");
		my_free (tmp);
	}
	return (NULL);
}

/**
 * @note if there are more than 1 path, it will ignore after the first.
 */
int	built_cd(char **input, t_data *data)
{
	char		*dest;
	char		*cur;
	char		*tmp_pwd;

	obtain_pwd_home(data, 0);
	cur = getcwd(NULL, 0);
	if (ft_strcmp("-", input[1]) == 0)
	{
		dest = get_dest_path_env(data, "OLDPWD");
		if (!dest)
			return (free (cur), 1);
	}
	tmp_pwd = obtain_pwd_home(data, 3);
	envp_cd_mod(&data->env, tmp_pwd, 2);
	if (!input[1])
		dest = get_dest_path_env(data, "HOME");
	else if (ft_strcmp("..", input[1]) && (ft_strcmp("./", \
	input[1]) == 0 || input[1][0] == '.'))
		dest = get_dest_path_wl_sign(cur, tmp_pwd, input[1], data);
	else if (ft_strcmp("-", input[1]) != 0)
		dest = get_dest_path(input[1], data);
//	ft_printf("before exit cd return: %d\n", data->return_val);
	envp_cd_mod(&data->env, dest, 1);
	obtain_pwd_home(data, 4);
	return (free (tmp_pwd), free (dest), free (cur), /*g_return_val*/data->return_val);
}
