/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-mada <bde-mada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 09:32:33 by bde-mada          #+#    #+#             */
/*   Updated: 2023/12/06 15:44:28 by bde-mada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/history.h>

/* int	check_exit(char **input)
{
	if (input[1])
		g_return_val = ft_atoi(input[1]);
	return (INT_MAX);
} */

/**
 * @note modified to control any kind of letters for pwd, echo, env
 * @note changed order of the conditions, I think will not make any
 * error because of this. tho....
 * It would be neat to make it a command Arr and pass function's pointer,
 * but it's readable, so leave it.
 * @note Input1 is empty now
 * @note cd, echo, pwd and env are not case sensitive
 */
int	check_builtin(char **input, t_data *data)
{
	char	*lower_input;

	if (!input[0])
		return (-1);
	update_last_executed_cmd(data, input);
	if (!ft_strcmp(input[0], "export"))
		return (built_export(input, data));
	if (!ft_strcmp(input[0], "unset"))
		return (built_unset(input, data));
	if (!ft_strcmp(input[0], "exit"))
		return (built_exit(input, data, data->cmd_nb));
	lower_input = ft_strdup(input[0]);
	ft_strlower(lower_input);
	if (!ft_strcmp(lower_input, "cd"))
		return (free(lower_input), built_cd(input, data));
	if (!ft_strcmp(lower_input, "echo"))
		return (free(lower_input), built_echo(input, data));
	if (!ft_strcmp(lower_input, "pwd"))
		return (free(lower_input), built_pwd(data));
	if (!ft_strcmp(lower_input, "env"))
		return (free(lower_input), built_env(input, data));
	return (free(lower_input), -1);
}

int	check_single_builtin(t_list *cmd_list, t_data *data)
{
	char	**cmd;
	int		return_val;

	cmd = fill_current_cmd(cmd_list, 0, data);
	if (!cmd)
		return (-1);
	return_val = check_builtin(cmd, data);
	free_list(cmd);
	if (return_val >= 0)
	{
		data->return_val = return_val;
		return (0);
	}
	return (1);
}

/* 	t_list *test = cmd_list;
	ft_printf(COLOR_CYAN"Printing list"COLOR_RESET"\n");
	while (test)
	{
		ft_printf("Content: %s type: %d pos: %d\n", test->content, \
					test->type, test->cmd_pos);
		test = test->next;
	} 
	ft_printf("\n");*/

int	process_input(char *line_read, t_data *data)
{
	t_list	*cmd_list;

	data->cmd_nb = lexer(line_read, &cmd_list, &data);
	if (data->cmd_nb == -1)
		return (1);
	if (data->cmd_nb == 0 && check_single_builtin(cmd_list, data) == 0)
		return (ft_lstclear(&cmd_list, free), 0);
	data->max_pid = 0;
	executer(cmd_list, data);
	ft_lstclear(&cmd_list, free);
	return (0);
}

/**
 * @note 231117nimai: this function is to check if the
 * 						command line is totally white.
 * @return if the entire line is white, free the string(line_read) and return 1.
  */
int	ft_entire_isspace(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!ft_isspace(str[i]))
			return (0);
	free (str);
	return (1);
}

int	minishell(t_data *data)
{
	char	*line_read;
	char	*prompt;

	prompt = get_prompt(data);
	while (1)
	{
		set_signal_handlers(1);
		line_read = readline(prompt);
		if (line_read == NULL)
			break ;
		if (line_read && *line_read)
		{
			add_history(line_read);
			if (ft_entire_isspace(line_read))
				continue ;
			process_input(line_read, data);
		}
		get_exit_status(data);
		line_read = my_free(line_read);
		//DELETE
		ft_printf(COLOR_BLUE"\nReturn val: %d\n", data->return_val);
		if (data->exit_status)
			break ;
	}
	ft_printf("\nBye 🗑\n");
	return (rl_clear_history(), free(prompt), obtain_pwd_home(NULL, 99), 0);
}
