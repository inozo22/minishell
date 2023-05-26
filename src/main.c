/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 12:52:29 by nimai             #+#    #+#             */
/*   Updated: 2023/05/26 10:14:23 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/**
 * @brief builtin command controler.
 * @author nimai
 * @param **av whatever receive, it's changeble.
 * @note to check cmd, I will put a function instead of this main.
 */
int	main(int ac, char **av)
{
//230523nimai: I don't think I will receive ac, so when I know what I receive, change it.
//Hope coming sth like **strs.
	if (ac < 2)
	{
		return (0);
	}
	if (ft_strncmp(av[1], "echo", ft_strlen(av[1])) == 0)
	{
		printf("I got echo\n");//kesu
		built_echo(av);
	}
	else if (ft_strncmp(av[1], "cd", ft_strlen(av[1])) == 0)
	{
		printf("I got cd\n");//kesu
		built_cd(av);
	}
	else if (ft_strncmp(av[1], "pwd", ft_strlen(av[1])) == 0)
	{
		printf("I got pwd\n");//kesu
		built_pwd(av);
	}
	else if (ft_strncmp(av[1], "export", ft_strlen(av[1])) == 0)
	{
		printf("I got export\n");//kesu
		built_export(av);
	}
/* 	else if (ft_strncmp(av[1], "unset", ft_strlen(av[1])) == 0)
	{
		printf("I got unset\n");//kesu
		built_unset(av);
	} */
	else if (ft_strncmp(av[1], "env", ft_strlen(av[1])) == 0)
	{
		printf("I got env\n");//kesu
		built_env(av);
	}
	else if (ft_strncmp(av[1], "exit", ft_strlen(av[1])) == 0)
	{
		printf("I got exit\n");//kesu
		built_exit(av);
	}
	else
	{
		ft_printf("minishell: %s: command not found\n", av[1]);
	}
	return (0);
}

