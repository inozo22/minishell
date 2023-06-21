/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 09:32:33 by bde-mada          #+#    #+#             */
/*   Updated: 2023/06/21 13:44:56 by nimai            ###   ########.fr       */
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

/**
 * @note 230615nimai: add protect for input null
 * @note 230619nimai: add input as a parametor for built_env
 */
static int	check_builtin(char **input, t_data *data)
{
/* 	int i = -1;
	while (data->env[++i])
		ft_printf("env %d: %s\n", i, data->env[i]); */
	//proteccion
	if (!input)
		return (-1);
	//proteccion
	ft_printf("Input0: %s\n", input[0]);
	if (!ft_strcmp(input[0], "echo"))
		return(built_echo(input));
	else if (!ft_strcmp(input[0], "cd"))
		return(built_cd(input, data));
	else if (!ft_strcmp(input[0], "pwd"))
		return(built_pwd(data));
	else if (!ft_strcmp(input[0], "export"))
		return(built_export(input, data));
	else if (!ft_strcmp(input[0], "unset"))
		return(built_unset(input, data));
	else if (!ft_strcmp(input[0], "env"))
		return(built_env(input, data));
	else if (!ft_strcmp(input[0], "exit"))
	{
		ft_printf("Exit found!\n");
		return(INT_MAX);
	}
	else
		return(-1);
}

static int process_input(char *line_read, t_data *data)
{
	int		i;
	int		j;
	char	**input;
/* 	lexer();
	parser();
	expanser(); */

	input = split_input(line_read);
	j = -1;
	while (input && input[++j])
		ft_printf("Input split %d: %s\n", j, input[j]);
	i = check_builtin(input, data);
	ft_printf("Check builtin return: %d\n", i);
	if (i == -1)
		ft_printf("Not a builtin\n");
	if (i == INT_MAX)
		return(check_exit(input, data));
//	del_array((void ***) &input);
	return (i);
}

int	minishell(t_data *data)
{
	char	*line_read;
	char	*prompt;

	prompt = get_prompt(data);
	while (1)
	{
		set_signal_handlers();
//------------------------------------------------------
/* 		int x= 0;

		while (x < av_amount(data->env))
		{
			ft_printf("env %d: %s\n", x, data->env[x]);
			x++;
		} */
//------------------------------------------------------
		line_read = readline(prompt);
		if (!line_read)
			sig_eof();
		if (line_read && *line_read)
			add_history(line_read);
		if (line_read && process_input(line_read, data) == INT_MAX)
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


