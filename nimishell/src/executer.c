/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 12:18:50 by bde-mada          #+#    #+#             */
/*   Updated: 2023/12/11 12:14:59 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>
#include <sys/types.h>//it's not necessary in POSIX.1

static int	child_execution(char **cmd, t_data *data, t_list *head)
{
	char	*cmd_path;
	int		return_val;
	char	**path;

	return_val = 0;
	path = set_path_list(data);
	cmd_path = get_cmd_path(cmd[0], path, &return_val);
	if (!cmd_path)
	{
		return_val = error_msg(cmd[0], return_val);
		free_list(cmd);
		free_alloc(data);
		exit(return_val);
	}
	if (execve(cmd_path, cmd, data->env) == -1 && errno == ENOEXEC)
		execute_script_without_shebang(cmd, data->env);
	ft_printf(SH_NAME": %s: %s\n", cmd[0], strerror(errno));
	ft_lstclear(&head, free);
	free_list(cmd);
	free_alloc(data);
	exit(EXIT_FAILURE);
}

static int	child(char **cmd, t_data *data, t_list *head)
{
	int		is_builtin;

	if (!cmd || !cmd[0])
		exit(EXIT_SUCCESS);
	if (!cmd[0][0])
		exit(error_msg("", 1));
	is_builtin = check_builtin(cmd, data);
	if (is_builtin >= 0)
	{
		free_list(cmd);
		exit(is_builtin);
	}
	child_execution(cmd, data, head);
	exit(EXIT_FAILURE);
}

/* int	check_pipe_redir(t_list *head, int pos)
{
	while (head && head->cmd_pos <= pos + 1)
	{
		if (head->cmd_pos == pos + 1 && head->type == HERE_DOC)
			return (1);
		head = head->next;
	}
	return (0);
} */

static void	father(char **cmd, int pos, t_data *data)
{
	free_list(cmd);
	close(data->pipe_fd[WRITE_END]);
	if (pos < data->cmd_nb)
	{
		dup2(data->pipe_fd[READ_END], STDIN_FILENO);
		close(data->pipe_fd[READ_END]);
	}
	if (pos == data->cmd_nb)
	{
		dup2(data->tmp_stdio_fd[0], STDIN_FILENO);
		close(data->tmp_stdio_fd[0]);
		dup2(data->tmp_stdio_fd[1], STDOUT_FILENO);
		close(data->tmp_stdio_fd[1]);
	}
}

static int	fork_setup(char **cmd, t_data *data, t_list *head, t_list *cmd_list)
{
	int	pos;

	pos = cmd_list->cmd_pos;
	if (pos < data->cmd_nb && pipe(data->pipe_fd) == -1)
		return (-1);
	if (get_heredoc_input(cmd_list, pos, data))
		return (data->return_val = 1, -1);
	data->return_val = 0;
	if (redir_setup(data, pos))
		return (-1);
	if (get_iofiles_fd(data->process_fd, cmd_list, pos, data))
	{
		data->return_val = 1;
		dup2(data->tmp_stdio_fd[0], STDIN_FILENO);
		return (-1);
	}
	data->max_pid = fork();
	if (data->max_pid == -1)
		return (-1);
	if (data->max_pid == 0)
		child(cmd, data, head);
	else
		father(cmd, pos, data);
	return (0);
}

int	executer(t_list *cmd_list, t_data *data)
{
	char	**cmd;
	int		pos;
	t_list	*head;

	head = cmd_list;
	set_fds(data, 1);
	while (cmd_list)
	{
		pos = cmd_list->cmd_pos;
		set_signal_handlers(0);
		cmd = fill_current_cmd(cmd_list, pos, data);
		update_last_executed_cmd(data, cmd);
		dup2(data->process_fd[READ_END], STDIN_FILENO);
		close(data->process_fd[READ_END]);
		if (fork_setup(cmd, data, head, cmd_list) == -1)
		{
			free_list(cmd);
			return (-1);
		}
		while (cmd_list && cmd_list->cmd_pos == pos)
			cmd_list = cmd_list->next;
	}
	return (0);
}
