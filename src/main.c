/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:23:03 by nimai             #+#    #+#             */
/*   Updated: 2023/06/08 11:58:33 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_temp	*read_line(char *line, t_temp *temp)
{
	char	**temp_av;

	temp_av = ft_split(line, 32);
	temp->argv = temp_av;
	return (temp);
}

t_temp	*init_temp(char *envp[], t_temp *temp)
{
	temp->i = 0;
	temp->argv = NULL;
	temp->envp = envp;
	return (temp);
}

/**
 * 
 */
void	minishell(char **envp)
{
	char	*line;
	int		ret;
	t_temp	*temp;


	ret = 0;
	/**
	 * 230526nimai: should be controled both length, av and command 

	 */
	temp = (t_temp *)malloc(sizeof(t_temp));
	if (!temp)
		return ;
	temp = init_temp(envp, temp);
	line = readline ("minishell🐚 > ");
	while (line)
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
		if (*line)
		{
			add_history(line);
			temp = read_line(line, temp);
			built_main(temp);
		}
		free (line);
		line = readline ("minishell🐚 > ");
	}
/* 	while (1)
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
			built_main(av, temp);
			ft_printf ("%s\n", line);
			add_history(line);
			free (line);
			line = readline ("minishell🐚 > ");
		}
	} */
	free (temp);
	write (1, "exit\n", 5);
	exit (0);
}

int	main(int ac, char **av, char **envp)
{
	(void)av;
	if (ac == 1)
		minishell(envp);
}
