/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 18:40:39 by nimai             #+#    #+#             */
/*   Updated: 2023/05/24 14:41:18 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_cd(char *cmd)
{
	ft_printf("minishell: cd: %s: No such file or directory\n", cmd);
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
	char	*ret;
	char	*cur;


	cur = getcwd(NULL, 0);
	if (ft_strncmp(cur, str, ft_strlen(cur)) == 0)
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
	{
		return (error_cd(str), NULL);
	}
	printf("Where am I: %s\n", getcwd(NULL, 0));
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

	cur = getcwd(NULL, 0);
	if (!cur)
		return ((error_cd("current directory")), 0);//230524nimai: if it's null, like doesn't exit the current directory, what should I do? give error, or ignore?
	if (!av[2])//when you don't have argument after "cd"
	{
		printf("Where am I: %s\n", getcwd(NULL, 0));
		if (chdir(getenv("HOME")) == -1)
		{
			printf("Line: %d\n", __LINE__);
			return (-1);
		}
		printf("Where am I: %s\n", getcwd(NULL, 0));
		printf("Line: %d\n", __LINE__);
		return (0);
	}
	printf("current position: %s\n", cur);
	dest = get_dest_path(av[2]);//230524nimai: after av[3] will be ignored.
	if (!dest)
		return (0);//230524nimai: if it's null, should it moves to home dir? Or just ignore it?
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
 */

