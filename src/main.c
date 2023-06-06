/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:23:03 by nimai             #+#    #+#             */
/*   Updated: 2023/06/06 16:39:45 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/**
 * 
 */
void	minishell(char **envp)
{
	char	*line;
	int		ret;

	ret = 0;
	(void)envp;
	while (1)
	{
		line = readline ("minishell🐚 > ");
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
		if (!line || ft_strlen(line) == 0)
		{
			free (line);
			break ;
		}
		ft_printf ("%s\n", line);
		add_history(line);
		free(line);
	}
	printf("exit\n");
	exit (1);
}

int	main(int ac, char **av, char **envp)
{
	(void)av;
	if (ac == 1)
		minishell(envp);
}
