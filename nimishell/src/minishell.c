/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 09:32:33 by bde-mada          #+#    #+#             */
/*   Updated: 2023/08/03 17:06:25 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_user(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		if (ft_strnstr(env[i], "USER=", 5))
			break ;
	if (env[i])
		return (ft_strdup(env[i] + 5));
	else
		return (NULL);
}

char	*get_prompt(t_data *data)
{
	char	*user;
	char	*prompt;
	int		prompt_len;
	int		color_len;

	user = get_user(data->env);
	prompt_len = ft_strlen(SHELL_NAME) + ft_strlen(user);
	color_len = ft_strlen(COLOR_ACCENT) + ft_strlen(COLOR_RESET) \
						+ ft_strlen(COLOR_BLUE) + ft_strlen(COLOR_RESET);
	prompt = (char *)ft_calloc(prompt_len + color_len + 5, sizeof(char));
	if (!prompt)
		return (NULL);
	ft_strcpy(prompt, COLOR_ACCENT);
	ft_strcat(prompt, SHELL_NAME);
	ft_strcat(prompt, COLOR_RESET);
	ft_strcat(prompt, COLOR_BLUE);
	ft_strcat(prompt, "@");
	ft_strcat(prompt, user);
	free(user);
	ft_strcat(prompt, COLOR_RESET);
	ft_strcat(prompt, "$ ");
	return (prompt);
}

int	check_exit(char **input, t_data *data)
{
	if (input[1])
		data->return_val = ft_atoi(input[1]);
	return (INT_MAX);
}

int	check_builtin(char **input, t_data *data)
{
/* 	int i = -1;
	while (data->env[++i])
		ft_printf("env %d: %s\n", i, data->env[i]); */
	if (!input || !input[0])
		return (-1);
	ft_printf("Input0: %s\n", input[0]);
	ft_printf("Input1: %s\n", input[1]);
	if (!ft_strcmp(input[0], "echo"))
		return (built_echo(input));
	else if (!ft_strcmp(input[0], "cd"))
		return (built_cd(input, data));
	else if (!ft_strcmp(input[0], "pwd"))
		return (built_pwd(data));
	else if (!ft_strcmp(input[0], "export"))
		return (built_export(input, data));
	else if (!ft_strcmp(input[0], "unset"))
		return (built_unset(input, data));
	else if (!ft_strcmp(input[0], "env"))
		return (built_env(input, data));
	else if (!ft_strcmp(input[0], "exit"))
	{
		ft_printf("Exit found!\n");
		return (INT_MAX);
	}
	else
		return (-1);
}

static int	process_input(char *line_read, t_data *data)
{
//	int		j;
//	char	**input;
	t_list	*cmd_list;
	int		cmd_nb;

	cmd_nb = lexer(line_read, &cmd_list);
	printf("cmd_nb: %d\n", cmd_nb);
	data->return_val = child_creation(NULL, NULL, cmd_list, cmd_nb, data->path, data->env, data);
	ft_lstclear(&cmd_list, free);
//	if (data->return_val == INT_MAX)
//		return (check_exit(input, data));
//	del_array((void ***) &input);
//	ft_printf("Command executed: %s with return: %d\n", input[0], data->return_val);
	return (data->return_val);
}

int	minishell(t_data *data)
{
	char	*line_read;
	char	*prompt;

	prompt = get_prompt(data);
	printf("pid in minishell: %d\n", data->pid);
	while (1)
	{
		//set_signal_handlers(13);
		set_signal_handlers(data->pid);//230802nimai: changed from above
		line_read = readline(prompt);
	/**
	 * KOKOMADE
	  */
		if (line_read && *line_read)
		{
/* 			if (!ft_strcmp(line_read, "^C"))
				rl_on_new_line();
			else *///230731nimai:comment
				add_history(line_read);
		}
		if (!line_read)//230731nimai: added to work ctrl+D without segfault
		{
			sig_eof();//check function process
			break ;
		}
		if (process_input(line_read, data) == INT_MAX)
			break ;
		free(line_read);
	}
	free(prompt);
	rl_redisplay();
	printf("\n\nBye 🗑");
	rl_clear_history();
	free(line_read);
	return (data->return_val);
}
//		 to use with SIGSTOP
//		rl_replace_line("New line", 1);
//		rl_on_new_line(); to use with SIGSTOP
