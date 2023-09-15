/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 18:40:39 by nimai             #+#    #+#             */
/*   Updated: 2023/09/15 11:27:14 by nimai            ###   ########.fr       */
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
	printf("cur: %s	\ndest: %s\nret: %s\n", cur, dest, ret);
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
	int		i;

	i = 0;
	while (data->env[i])
	{
		if (ft_strnstr(data->env[i], "PWD=", 4))
			break ;
		i++;
	}
	if (!data->env[i])
	{
		ret = getcwd(NULL, 0);
		return (ret);
	}
	return (ft_strdup(data->env[i] + 4));
}

/**
 * @note should be modified, but yet IDK if it's work with the current directory absense, so after merge check and modify
 */
int	built_cd(char **input, t_data *data)
{
	char		*dest;
	char		*cur;
	static char	*pwd = NULL;

	g_return_val = 0;
	if (!pwd)
		pwd = init_pwd(data);
	if (!input)
		return (ft_printf("%s\n", pwd), 0);
	cur = getcwd(NULL, 0);
	if (/* cur &&  */ft_strcmp("-", input[1]) == 0)//you have to obtain OLDPWD to move before change it
	{
		dest = get_dest_path_env(data, "OLDPWD");
		if (!dest)
			return (free (cur), 1);
	}
	data = envp_cd_mod(data, pwd, 2);//write OLDPWD

	printf("%sOLDPWD: %s%s\n", COLOR_YELLOW, pwd, COLOR_RESET);
	printf("%sinput[1]: %s%s\n", COLOR_YELLOW, input[1], COLOR_RESET);
	if (!input[1] || !ft_strcmp(input[1], "~"))//when you don't have argument after "cd", move to $HOME
		dest = get_dest_path_env(data, "HOME");
	else if (ft_strcmp("./", input[1]) == 0 || input[1][0] == '.'/* ft_strncmp(".", input[1], 1 == 0) */)
		dest = get_dest_path_wl_sign(cur, pwd, input[1]);
	else if (ft_strcmp("-", input[1]) != 0)
		dest = get_dest_path(input[1]);//230524nimai: after av[3] will be ignored.
	pwd = mod_pwd(pwd, dest);

	printf("%sPWD: %s%s\n", COLOR_YELLOW, pwd, COLOR_RESET);
	printf("%sgetcwd: %s%s\n", COLOR_YELLOW, getcwd(NULL, 0), COLOR_RESET);

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

