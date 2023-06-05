/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 18:40:39 by nimai             #+#    #+#             */
/*   Updated: 2023/06/05 16:09:23 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* char	*ft_strlower(char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = str;
	while (tmp[i])
	{
		tmp[i] = ft_tolower(str[i]);
		i++;
	}
	return (tmp);
} */

/* char	*str_mod(char *cur, char *str, int i)
{
	int	j;

	j = 0;
	while (cur[i])
	{
		cur[i] = str[j];
		i++;
		j++;
	}
	return (cur);
} */

/* char	*path_modify(char *cur, char *str)
{
	int		i;
	char	*tmp;

	tmp = malloc(ft_strlen(str) + 1);
	ft_strlcpy(tmp, str, ft_strlen(str) + 1);
	ft_strlower(tmp);
//	printf("str: %s\n", str);
//	printf("tmp: %s\n", tmp);
	i = ft_strnstr_int(cur, tmp, ft_strlen(cur));
	cur = str_mod(cur, str, i);
	free (tmp);
//	printf("cur: %s\n", cur);
//	exit (1);
	return (cur);
} */


/**
 * @brief add environment according to dest in **
 * @author nimai
 * @return ** pointer, then free 
 * @note 230603nimai: Doesn't show PWD on Ubuntu (moji bake)
 */
/* void	envp_pwd_mod(t_temp *temp, char *dest)
{
	int		i;
	char	**tmp;
	int		x;

	i = 0;
	tmp = (char **)temp->envp;
	while (tmp[i])
	{
		if (ft_strncmp(tmp[i], "PWD", 3) == 0)
		{
			tmp[i] = NULL;
			tmp[i] = ft_strjoin("PWD=", dest);
			x = i;
		}
		i++;
	}
	temp->envp = tmp;
	free (tmp[x]);
} */

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

char	*get_dest_path(char *str)
{
	char	*ret;
	char	*cur;
	int		cut;

	ret = NULL;
	cur = NULL;
	if (ft_strncmp("../", str, ft_strlen(str)) == 0)
	{
		cur = getcwd(NULL, 0);
		cut = get_pos_above_path(cur);
		ret = malloc(sizeof(char) * (cut + 1));
		if (!ret)
			return (heap_error(1), NULL);
		ft_strlcpy(ret, cur, cut + 1);
		chdir(ret);
		return (free (cur), ret);
	}
	else//case absolute path
	{
		if (chdir(str) == -1)
			return (error_cd(str), NULL);
		cur = getcwd(NULL, 0);
		if (ft_strlen(cur) > ft_strlen(str))			//path is a relative one, modify the path
		{
			cur = path_modify(cur, str);
			return (cur);
		}
		return (free (cur), str);		//str is an absolute path, so pass it directory
	}
	return (ret);
}

/**
 * @brief manage "builtin" cd cmd.
 * @author nimai
 * @param **av "cd", "path".
 * @return 
 */
int	built_cd(t_temp *temp)
{
	char	*dest;
	char	*cur;
	char	*test;

	cur = getcwd(NULL, 0);
//printer
	printf("Line: %d:	", __LINE__);
	printf("position before	:	%s\n", cur);
//printer
	if (!cur)
		return ((error_cd("current directory")), 0);//230524nimai: if it's null, like doesn't exit the current directory, what should I do? give error, or ignore?
	if (!temp->argv[2])//when you don't have argument after "cd", move to $HOME
	{
		if (chdir(getenv("HOME")) == -1)
			return (printf("Line: %d, failed chdir\n", __LINE__), -1);
	}
	else if (ft_strncmp("./", temp->argv[2], 2) == 0)//don't move, but if it's not exist
		chdir(cur);
	else
	{
		dest = get_dest_path(temp->argv[2]);//230524nimai: after av[3] will be ignored.
		if (!dest)
			return (free (cur), -1);	//230524nimai: if it's null, should it moves to home dir? Or just ignore it?
		envp_pwd_mod(temp, dest);
		printf("\n		===TEST CD===\n");
		built_env(temp);
		printf("		===TEST CD===\n");
		if (ft_strncmp(dest, temp->argv[2], ft_strlen(dest)) != 0)
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
 * How to managge errors? At this moment, put in each function.
 * 
 * TODO list
 * - change env!
 * - check if it has / or not.
 */

