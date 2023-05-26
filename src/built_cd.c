/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 18:40:39 by nimai             #+#    #+#             */
/*   Updated: 2023/05/26 09:36:11 by nimai            ###   ########.fr       */
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

/**
 * @brief check if the path exists.
 * @author nimai
 * @note 
 */
bool	check_path(char *str)
{
	(void)str;
/* 	while ()
	{
		
	} */
	return (1);
}

/**
 * @brief get path length.
 * @author nimai
 * @note will be eliminated
 */
/* int	get_path_length(char *str, int i)
{
	int	ret;

	ret = 0;
	while (str[i])
	{
		ret++;
		i++;
	}
	return (ret);
}
 */
/**
 * @brief get absolute path to move
 * @author nimai
 * @return destination path as string
 */
char	*get_dest_path(char *str)
{
	char	*ret = NULL;
	char	*cur;
	int		cut;

	cur = getcwd(NULL, 0);
	if (ft_strncmp("../", str, 3) == 0)
	{
		cut = get_pos_above_path(getcwd(NULL, 0));
		ret = malloc(sizeof(char) * cut + 1);
		if (!ret)
			return (heap_error(1), NULL);
		ft_strlcpy(ret, getcwd(NULL, 0), cut + 1);
		return (ret);
	}
	else if (ft_strncmp(cur, str, ft_strlen(cur)) == 0)
	{
		printf("Maybe I have absolute path\n");
		return (str);//maybe it's absolute path		
	}
	else if (ft_strncmp(getenv("HOME"), str, ft_strlen(getenv("HOME"))) == 0)
	{
		printf("Maybe I have absolute path, but shorter\n");
		return (str);//maybe it's absolute path		
	}
	ret = ft_calloc(sizeof(char), ft_strlen(cur) + ft_strlen(str) + 1);
	ft_strlcpy(ret, cur, ft_strlen(cur) + 1);//copy the cur string
	ft_strlcat(ret, str, ft_strlen(cur) + ft_strlen(str) + 1);
/* 	if (!check_path(str))
		return (error_cd(str), NULL); */
	printf("ret: %s\n", ret);
	printf("cur: %s\n", cur);
	printf("str: %s\n", str);
	printf("Where am I: %s\n", getcwd(NULL, 0));
	if (chdir(ret) == -1)
		return (error_cd(str), NULL);
	printf("Where am I: %s\n", getcwd(NULL, 0));
	if (ret)
		free (ret);
	exit(1);

	return (ret);
}

/**
 * @brief manage "builtin" cd cmd.
 * @author nimai
 * @param **av "cd", "path".
 * @return 
 */
int	built_cd(char **av)
{
	char	*dest;
	char	*cur;
	char	*test;

	cur = getcwd(NULL, 0);
	if (!cur)
		return ((error_cd("current directory")), 0);//230524nimai: if it's null, like doesn't exit the current directory, what should I do? give error, or ignore?
	if (!av[2])//when you don't have argument after "cd"
	{
		printf("Where am I: %s\n", test = getcwd(NULL, 0));
		free (test);
		if (chdir(getenv("HOME")) == -1)
		{
			printf("Line: %d\n", __LINE__);
			return (-1);
		}
		printf("Where am I: %s\n", test = getcwd(NULL, 0));
		free (test);
		printf("Line: %d\n", __LINE__);
		free (cur);
		return (0);
	}
	if (ft_strncmp("./", av[2], ft_strlen(av[2])) == 0)
		return (0);
	printf("Line: %d\n", __LINE__);
	printf("current position: %s\n", cur);
	dest = get_dest_path(av[2]);//230524nimai: after av[3] will be ignored.
	if (!dest)
		return (0);//230524nimai: if it's null, should it moves to home dir? Or just ignore it?
	
	if (chdir(dest) == -1)
	{
		free (dest);
		free (cur);
		return (error_cd(av[2]), 1);
	}
	free (dest);
	free (cur);
	printf("Where am I: %s\n", test = getcwd(NULL, 0));
	free (test);
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
 * /users/nimai/42/42cursus/minishell/inc    <= ?????
 * 
 * printf("line: %d\n", __LINE__);
 * error message: ft_printf("No such file or directory\n");
 * how to treat "../" or "./", give message like above? Or put other message? Also fine move to old folder with $OLDPATH
 * How to managge errors? At this moment, put in each function.
 * 
 * TODO list
 * - change env!
 * - check if it has / or not.
 */

