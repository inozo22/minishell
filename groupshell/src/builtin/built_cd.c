/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 18:40:39 by nimai             #+#    #+#             */
/*   Updated: 2023/06/09 10:10:54 by nimai            ###   ########.fr       */
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
	ft_printf("minishell: cd: %s: No such file or directory\n", cmd);
}

/**
 * @brief obtain above path from array
 * @author nimai
 * @note 
 */
int	get_pos_above_path(char *str)
{
	int		len;

	len = ft_strlen(str);
	while (str[--len])
	{
		if (str[len] == '/')
		{
			break ;
		}
	}
	return (len);
}

char	*get_above_path(char *cur)
{
	int		cut;
	char	*ret;

	cut = get_pos_above_path(cur);
	ret = malloc(sizeof(char) * (cut + 1));
	if (!ret)
		return (heap_error(1), NULL);
	ft_strlcpy(ret, cur, cut + 1);
	if (chdir(ret) == -1)
		return (error_cd(ret), NULL);
	return (ret);
}

char	*get_dest_path(char *dest)
{
	char	*ret;
	char	*cur;

	ret = NULL;
	cur = NULL;
	if (ft_strncmp("../", dest, ft_strlen(dest)) == 0)
	{
		cur = getcwd(NULL, 0);
		ret = get_above_path(cur);
		return (free (cur), ret);
	}
	else//case absolute path
	{
		if (chdir(dest) == -1)
			return (error_cd(dest), NULL);
		cur = getcwd(NULL, 0);
		if (ft_strlen(cur) > ft_strlen(dest))			//path is a relative one, modify the path
		{
			cur = path_modify(cur, dest);
			return (cur);
		}
		return (free (cur), dest);		//seems that str is an absolute path, so pass it directory
	}
	return (ret);
}

/**
 * @brief manage "builtin" cd cmd.
 * @author nimai
 * @param **av "cd", "path".
 * @return 
 * @note 
 */
int	built_cd(char **input, t_data *data)
{
	char	*dest;
	char	*cur;
	char	*test;

	cur = getcwd(NULL, 0);
//printer
	printf("Line: %d:	", __LINE__);
	printf("position before	:	%s\n", cur);
	printf("Line: %d:	av[0]: %s, av[1]: %s\n", __LINE__, input[0], input[1]);
//printer
	if (cur && !input[1])//when you don't have argument after "cd", move to $HOME
	{
		if (chdir(getenv("HOME")) == -1)
			return (printf("Line: %d, failed chdir\n", __LINE__), -1);
		envp_pwd_mod(data, getenv("HOME"));
	}
	else if (cur && ft_strncmp("./", input[1], 2) == 0)//move to where you are, you will get OLDPWD
		chdir(cur);
	else if (!cur && ft_strncmp("./", input[1], 2) == 0)//move to where you are, but if it's not exist
	{
		dest = ft_strjoin(getenv("PWD"), input[1]);
		data = envp_pwd_mod(data, dest);
		free (dest);
		ft_printf("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory");//temporary error control
		return (0);//it should be return (0), as bash works
	}
	else
	{
		dest = get_dest_path(input[1]);//230524nimai: after av[3] will be ignored.
		if (!dest)
			return (free (cur), 1);	//230524nimai: if it's null, should it moves to home dir? Or just ignore it?
		envp_pwd_mod(data, dest);
		if (ft_strncmp(dest, input[1], ft_strlen(dest)) != 0)
			free (dest);
	}
	free (cur);
//printer
	test = getcwd(NULL, 0);
	printf("Line: %d:	", __LINE__);
	printf("position after	:	%s\n", test);
	free (test);
//printer
	return (0);
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
 * 230605 OLDPWD hasn't added yet, add when you know the structure(more or less)
 * 
 * cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory
 * bash-3.2$ echo $?
 * 0
 * bash-3.2$ pwd
 * /Users/nimai/test_bash/./
 * 
 */
