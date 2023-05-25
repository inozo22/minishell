/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 10:18:56 by nimai             #+#    #+#             */
/*   Updated: 2023/05/25 13:02:42 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief temporary error management
 * @author nimai
 * @note when dicided error management, chang it.
 */
void	error_export(char *cmd)
{
	ft_printf("minishell: cd: %s: No such file or directory\n", cmd);
}

/**
 * @brief obtain above path from array
 * @author nimai
 * @note 
 */


/**
 * @brief check if the path exists.
 * @author nimai
 * @note 
 */


/**
 * @brief get path length.
 * @author nimai
 * @note will be eliminated
 */
int	get_amount_ptr(char	**ptr)
{
	int	ret;

	ret = 0;
	while (ptr[ret])
	{
		ret++;
	}
	return (ret);
}

/**
 * @brief get absolute path to move
 * @author nimai
 * @param environ I think grab extern char **environ is ilegal, talk to Borja
 * @return destination path as string
 */
char	**fake_env(void)
{
	extern char	**environ;
	char		*val;
	char		**ret;
	int			i;
	int			plen;

	i = 0;
	plen = get_amount_ptr(environ);
	ret = malloc(sizeof(char *) * (plen + 1));
	while (i < plen)
	{
		val = malloc(ft_strlen(environ[i]) + 1);
		if (!val)
			return (NULL);
		val = environ[i];
		if (val)
			*ret = val;
//		free (val);
		i++;
		ret++;
	}
	return (ret);
}



/**
 * @brief manage "builtin" export cmd.
 * @author nimai
 * @param **av "export", "ABC=abc".
 * @return 
 */
int	built_export(char **av)
{
//	t_export	list[ARGLIMIT];
	char		**tmp_env;

	(void)av;
	tmp_env = fake_env();
	while (*tmp_env)
	{
		printf("%s", *tmp_env);
		tmp_env++;
	}



    return 0;




	
/* 	char	*dest;
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
	return (0); */
}

/**
 * BEHAVIOUR IN BASH
 * when execute export, the list should be ascending order, 
 * separated by capital letter and small letter
 * 
 * 
 */
