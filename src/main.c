/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:23:03 by nimai             #+#    #+#             */
/*   Updated: 2023/06/07 13:18:25 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_temp	*init_temp(char *av[], char *envp[], t_temp *temp)
{
	temp->i = 0;
	temp->argv = av;
	temp->envp = envp;
	printf("Line: %d\n", __LINE__);
	return (temp);
}

/**
 * 
 */
void	minishell(int ac, char **av, char **envp)
{
	char	*line;
	int		ret;
	t_temp	*temp;

	(void)ac;
	ret = 0;
	/**
	 * 230526nimai: should be controled both length, av and command 

	 */
	temp = (t_temp *)malloc(sizeof(t_temp));
	temp = init_temp(av, envp, temp);
	while (1)
	{
		if (signal(SIGINT, &sig_int_input) == SIG_ERR)
		{
			ft_printf("Line: %d, ERROR\n", __LINE__);
			exit (1);
		}
		if (signal(SIGQUIT, &sig_quit_input) == SIG_ERR)
		{
			ft_printf("Line: %d, ERROR\n", __LINE__);
			exit (1);
		}
		line = readline ("minishell🐚 > ");
		if (line && ft_strlen(line) > 0)
		{
			printf("Line: %d\n", __LINE__);
			built_main(av, temp);
			printf("Line: %d\n", __LINE__);
			ft_printf ("%s\n", line);
			add_history(line);
			free (line);
		}
	}
	printf("exit\n");
	exit (1);
}

int	main(int ac, char **av, char **envp)
{
	if (ac == 1)
		minishell(ac, av, envp);
}
