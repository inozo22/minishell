/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-mada <bde-mada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 12:52:29 by nimai             #+#    #+#             */
/*   Updated: 2023/06/08 15:36:52 by bde-mada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* t_data	*init_data(char *av[], char *envp[], t_data *temp)
{
	temp->i = 0;
	temp->argv = av;
	temp->envp = envp;
	return (temp);
}
 */

/**
 * @brief builtin command controler.
 * @author nimai
 * @param **av whatever receive, it's changeble.
 * @note to check cmd, I will put a function instead of this main.
 */
int	built_main(t_data *temp)
{
/* 	t_data	*temp;

	if (ac < 2)
		return (0); */
	/**
	 * 230526nimai: should be controled both length, av and command 

	 */
/* 	temp = (t_data *)malloc(sizeof(t_data));
	temp = init_data(av, envp, temp); */
//printer
	printf("temp->argv:	%s\n", temp->argv[0]);
	printf("temp->argv:	%s\n", temp->argv[1]);
//printer
	if (ft_strncmp(temp->argv[0], "echo", ft_strlen(temp->argv[0])) == 0 && \
	ft_strncmp(temp->argv[0], "echo", 4) == 0)
	{
		printf("🐚I got echo🎤\n");//kesu
		built_echo(temp);
	} 
	else if (ft_strncmp(temp->argv[0], "cd", ft_strlen(temp->argv[0])) == 0 \
	&& ft_strncmp(temp->argv[0], "cd", 2) == 0)
	{
		printf("🐚I got cd🚙\n");//kesu
		built_cd(temp);
	}
	else if (ft_strncmp(temp->argv[0], "pwd", ft_strlen(temp->argv[0])) == 0 \
	&& ft_strncmp(temp->argv[0], "pwd", 3) == 0)
	{
		//printf("🐚I got pwd🏠\n");//kesu
		built_pwd(temp);
	}
	else if (ft_strncmp(temp->argv[0], "export", ft_strlen(temp->argv[0])) == 0 \
	&&  ft_strncmp(temp->argv[0], "export", 6) == 0)
	{
		printf("🐚I got export📠\n");//kesu
		built_export(temp);
	}
	else if (ft_strncmp(temp->argv[0], "unset", ft_strlen(temp->argv[0])) == 0 \
	&& ft_strncmp(temp->argv[0], "unset", 5) == 0)
	{
		printf("🐚I got unset🧨\n");//kesu
		built_unset(temp);
	}
	else if (ft_strncmp(temp->argv[0], "env", ft_strlen(temp->argv[0])) == 0 \
	&& ft_strncmp(temp->argv[0], "env", 3) == 0)
	{
		printf("🐚I got env📑\n");//kesu
		built_env(temp);
	}
	else if (ft_strncmp(temp->argv[0], "exit", ft_strlen(temp->argv[0])) == 0 \
	&& ft_strncmp(temp->argv[0], "exit", 4) == 0)
	{
		printf("🐚I got exit🛫\n");//kesu
		built_exit(temp);
	}
	else
	{
		ft_printf("minishell: %s: command not found\n", temp->argv[0]);
	}
	//free (temp);
	//system ("leaks minishell");
	return (0);
}

