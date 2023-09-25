/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 18:40:39 by nimai             #+#    #+#             */
/*   Updated: 2023/09/18 11:15:53 by nimai            ###   ########.fr       */
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
	g_return_val = 1;
	ft_printf("minishell: cd: %s: No such file or directory\n", cmd);
}

/**
 * @brief obtain destination path
 * @author nimai
 */
char	*get_dest_path(char *dest)
{
	char	*ret;
	char	*cur;

	if (chdir(dest) == -1)
		return (g_return_val = 1, error_cd(dest), NULL);
	cur = getcwd(NULL, 0);
	ret = ft_strdup(dest);
	if (ft_strlen(cur) > ft_strlen(ret) && ft_strncmp("..", ret, 2) != 0)
		return (path_modify(cur, ret));
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

static char	*mod_pwd(char *pwd, char *dest)
{
	if (dest)
	{
		free (pwd);
		return (ft_strdup(dest));
	}
	return (pwd);
}

/**
 * @note to fill static pwd in cd function, if there is no PWD in env, obtain by getcwd.
 */
static char	*init_pwd(t_data *data)
{
	char	*ret;
	char	*tmp;
	int		i;

	i = 0;
	ret = getcwd(NULL, 0);
	while (data->env[i])
	{
		if (ft_strnstr(data->env[i], "PWD=", 4))
		{
			tmp = ft_strdup(data->env[i] + 4);
			break ;
		}
		i++;
	}
	if (!data->env[i])
	{
	//	ret = getcwd(NULL, 0);
		return (ret);
	}
	if (ft_strlen(ret) > ft_strlen(tmp))
		return (free (tmp), ret);
	return (free (tmp), free (ret), ft_strdup(data->env[i] + 4));
}

/**
 * @note should be modified, but yet IDK if it's work with the current directory absense, so after merge check and modify
 * @param flag if it's positive, to delete static char
 */
int	built_cd(char **input, t_data *data, int flag)
{
	char		*dest;
	char		*cur;
	static char	*pwd = NULL;

	if (flag == 1)
	{
		printf("before free pwd: %s\n", pwd);

		printf("flag is 1, exit from here!\n");
		free (pwd);
		pwd = NULL;
		printf("after free pwd: %s\n", pwd);
		return (0);
	}
	g_return_val = 0;
	if (!pwd)
		pwd = init_pwd(data);
	if (!input)
		return (ft_printf("%s\n", pwd), 0);
	cur = getcwd(NULL, 0);
	if (ft_strcmp("-", input[1]) == 0)
	{
		dest = get_dest_path_env(data, "OLDPWD");
		if (!dest)
			return (free (cur), 1);
	}
	data = envp_cd_mod(data, pwd, 2);
	if (!input[1] || !ft_strcmp(input[1], "~"))
		dest = get_dest_path_env(data, "HOME");
	else if (ft_strcmp("./", input[1]) == 0 || input[1][0] == '.')
		dest = get_dest_path_wl_sign(cur, pwd, input[1]);
	else if (ft_strcmp("-", input[1]) != 0)
		dest = get_dest_path(input[1]);
	pwd = mod_pwd(pwd, dest);
	return (envp_cd_mod(data, dest, 1), free (dest), free (cur), g_return_val);
}

/**
 * if there are more than 1 path, it will ignore after the first.
 * 
 * /Users/nimai/42/42cursus/minishell/inc
 * bash-3.2$ cd ..
 * bash-3.2$ ls
 * Makefile	README.md	inc		lib		minishell	questions.txt	src		test.dat
 * bash-3.2$ cd /users/nimai/42/42cursus/minishell/inc
 * bash-3.2$ pwd
 * /users/nimai/42/42cursus/minishell/inc    <= ????? ->done
 * 
 * printf("line: %d\n", __LINE__);
 * error message: ft_printf("No such file or directory\n");
 * how to treat "../" or "./", give message like above? -> treat how does work bash
 * 
 * How to managge errors? At this moment, put in each function.
 * 
 * TODO list
 * 230605 OLDPWD hasn't added yet, add when you know the structure(more or less) ->done
 * 
 * cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory
 * bash-3.2$ echo $?
 * 0
 * bash-3.2$ pwd
 * /Users/nimai/test_bash/./
 * 
 * bash-3.2$ cd -
 * bash: cd: OLDPWD not set
 * bash-3.2$ echo $?
 * 1
 * bash-3.2$ -> done
 * 
 */

