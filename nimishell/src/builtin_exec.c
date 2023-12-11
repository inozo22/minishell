/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-mada <bde-mada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:41:14 by bde-mada          #+#    #+#             */
/*   Updated: 2023/12/11 15:51:31 by bde-mada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	if (!input || !input[0])
		return (-1);
	update_last_executed_cmd(data, input);
	if (!ft_strcmp(input[0], "export"))
		return (built_export(input, data, 0));
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

static int	redir_single_builtin(t_list *cmd_list, t_data *data)
{
	if (get_iofiles_fd(data->process_fd, cmd_list, 0, data))
	{
		data->return_val = 1;
		dup2(data->tmp_stdio_fd[0], STDIN_FILENO);
		return (-1);
	}
	return (0);
}

int	check_single_builtin(t_list *cmd_list, t_data *data)
{
	char	**cmd;
	int		return_val;

	cmd = NULL;
	cmd = fill_current_cmd(cmd_list, 0, data);
	if (!cmd || !*cmd)
		return (data->return_val = 0, -1);
	if (!**cmd)
	{
		free_list(cmd);
		return (error_msg("", 1), data->return_val = 127, 127);
	}
	if (redir_single_builtin(cmd_list, data) == -1)
		return (-1);
	return_val = check_builtin(cmd, data);
	dup2(data->tmp_stdio_fd[0], STDIN_FILENO);
	dup2(data->tmp_stdio_fd[1], STDOUT_FILENO);
	free_list(cmd);
	if (return_val >= 0)
	{
		if (data->return_val == 0)
			data->return_val = return_val;
		return (0);
	}
	return (1);
}
