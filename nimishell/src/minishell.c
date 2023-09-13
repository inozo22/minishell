/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-mada <bde-mada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 09:32:33 by bde-mada          #+#    #+#             */
/*   Updated: 2023/09/12 20:27:16 by bde-mada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @note 230804nimai: at the moment, when there is no environment valur,
 * user name will be "noname"
  */
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
		return (ft_strdup("noname"));
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
	color_len = ft_strlen(COLOR_YELLOW) + ft_strlen(COLOR_RESET) + \
	ft_strlen(COLOR_BLUE) + ft_strlen(COLOR_RESET);
	prompt = (char *)ft_calloc(prompt_len + color_len + 5, sizeof(char));
	if (!prompt)
		return (NULL);
	ft_strcpy(prompt, COLOR_YELLOW);
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

int	check_exit(char **input)
{
	if (input[1])
		g_return_val = ft_atoi(input[1]);
	return (INT_MAX);
}

/**
 * @note modified to control any kind of letters for pwd, echo, env
 * @note changed order of the conditions, I think will not make any
 * error because of this. tho....
 * It would be neat to make it a command Arr and pass function's pointer,
 * but it's readable, so leave it.
 * @note Input1 is empty now
 * @note cd, echo, pwd and env are not case sensitive
 */
/* 	int	j = -1;
	while (input[++j])
		ft_printf("Input %d: %s\n", j, input[j]); */
int	check_builtin(char **input, t_data *data)
{
	char	*lower_input;
/* 	int i = -1;
	while (data->env[++i])
		ft_printf("env %d: %s\n", i, data->env[i]); */
//	update_last_executed_cmd(data, input[0]);
	if (!input[0])
		return (-1);
	if (!ft_strcmp(input[0], "export"))
		return (built_export(input, data));
	if (!ft_strcmp(input[0], "unset"))
		return (built_unset(input, data));
	if (!ft_strcmp(input[0], "exit"))
		return (built_exit(input, data, 1));
	lower_input = ft_strdup(input[0]);
	ft_strlower(lower_input);
	if (!ft_strcmp(lower_input, "cd"))
		return (free(lower_input), built_cd(input, data));
	if (!ft_strcmp(lower_input, "echo"))
		return (free(lower_input), built_echo(input));
	if (!ft_strcmp(lower_input, "pwd"))
		return (free(lower_input), built_pwd(data));
	if (!ft_strcmp(lower_input, "env"))
		return (free(lower_input), built_env(input, data));
	free(lower_input);
	return (-1);
}

int	process_input(char *line_read, t_data *data)
{
	t_list	*cmd_list;
	t_list	*tmp;
	int		cmd_nb;

	cmd_nb = lexer(line_read, &cmd_list);
	if (cmd_nb == -1)
		return (1);
	tmp = cmd_list;
	if (cmd_nb == 0)
	{
		while (tmp)
		{
			//SET THE EXIT INPUT FROM NULL TO DOUBLE ARRAY
			if (tmp->type == WORD && !ft_strcmp(tmp->content, "exit") && built_exit(NULL, data, 0) == 0)
			{
				ft_lstclear(&cmd_list, free);
				return (0);
			}
			tmp = tmp->next;
		}
	}
	g_return_val = executer(NULL, cmd_list, cmd_nb, data->path, data->env, data);
	ft_lstclear(&cmd_list, free);
	return (g_return_val);
}

int	minishell(t_data *data)
{
	char			*line_read;
	char			*prompt;

	prompt = get_prompt(data);
	while (1)
	{
		set_signal_handlers(1); //230808nimai: changed from above, to recall it after child process
		line_read = readline(prompt);
		if (!line_read)
		{
			g_return_val = 0;
			break ;
		}
		if (*line_read)
			add_history(line_read);
		process_input(line_read, data);
		ft_printf("\n\nReturn val: %d\n", g_return_val);
		if (data->exit_status)
			break ;
		free(line_read);
	}
	rl_clear_history();
	free(line_read);
	free(prompt);
	printf("\nBye 🗑\n");
	return (0);
}
