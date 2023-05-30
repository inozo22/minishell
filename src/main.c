/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 12:52:29 by nimai             #+#    #+#             */
/*   Updated: 2023/05/30 12:14:06 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_temp	*init_temp(char *av[], char *envp[], t_temp *temp)
{
	temp->i = 0;
	temp->argv = av;
	temp->envp = envp;
	return (temp);
}


/**
 * @brief builtin command controler.
 * @author nimai
 * @param **av whatever receive, it's changeble.
 * @note to check cmd, I will put a function instead of this main.
 */
int	main(int ac, char *av[], char *envp[])
{
	t_temp	*temp;
	if (ac < 2)
		return (0);
	/**
	 * 230526nimai: should be controled both length, av and command 
	 */
	temp = (t_temp *)malloc(sizeof(t_temp));
	temp = init_temp(av, envp, temp);
	if (ft_strncmp(av[1], "echo", ft_strlen(av[1])) == 0 && \
	ft_strncmp(av[1], "echo", 4) == 0)
	{
		printf("I got echo\n");//kesu
		built_echo(av);
	}
	else if (ft_strncmp(av[1], "cd", ft_strlen(av[1])) == 0 \
	&& ft_strncmp(av[1], "cd", 2) == 0)
	{
		printf("I got cd\n");//kesu
		built_cd(av);
	}
	else if (ft_strncmp(av[1], "pwd", ft_strlen(av[1])) == 0 \
	&& ft_strncmp(av[1], "pwd", 3) == 0)
	{
		printf("I got pwd\n");//kesu
		built_pwd(av);
	}
	else if (ft_strncmp(av[1], "export", ft_strlen(av[1])) == 0 \
	&&  ft_strncmp(av[1], "export", 6) == 0)
	{
		printf("I got export\n");//kesu
		built_export(av);
	}
	else if (ft_strncmp(av[1], "unset", ft_strlen(av[1])) == 0 \
	&& ft_strncmp(av[1], "unset", 5) == 0)
	{
		printf("I got unset\n");//kesu
		built_unset(av);
	}
	else if (ft_strncmp(av[1], "env", ft_strlen(av[1])) == 0 \
	&& ft_strncmp(av[1], "env", 3))
	{
		printf("I got env\n");//kesu
		built_env(av);
	}
	else if (ft_strncmp(av[1], "exit", ft_strlen(av[1])) == 0 \
	&& ft_strncmp(av[1], "exit", 4) == 0)
	{
		printf("I got exit\n");//kesu
		built_exit(av);
	}
	else
	{
		ft_printf("minishell: %s: command not found\n", av[1]);
	}

	/* int	i = 0;

	while (envp[i])
	{
		printf("%d: %s\n", i, envp[i]);
		i++;
	} */

	
	return (0);
}

