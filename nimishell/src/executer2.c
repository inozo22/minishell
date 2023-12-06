/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-mada <bde-mada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 12:18:50 by bde-mada          #+#    #+#             */
/*   Updated: 2023/12/06 16:51:12 by bde-mada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>
#include <sys/types.h>//it's not necessary in POSIX.1

/* int	get_heredoc_input(t_list *lst, int pos, t_data *data)
{
	char	*tmp_eof;

	tmp_eof = NULL;
	while (lst && lst->cmd_pos == pos)
	{
		if (lst->type == HERE_DOC)
		{
			tmp_eof = lst->content;
			ft_printf("tmp_eof: %s\n", tmp_eof);
		}
		lst = lst->next;
	}
	if (tmp_eof && heredoc_read(tmp_eof, data))
		return (1);
	return (0);
} */

int	child_execution(char **cmd, char **path, t_data *data, int pos)
{
	char	*cmd_path;
	int		return_val;

	return_val = 0;
	cmd_path = get_cmd_path(cmd[0], path, &return_val);
	if (!cmd_path)
	{
		return_val = error_msg(cmd[0], return_val);
		free_list(cmd);
		free_alloc(data);
		exit(return_val);
	}
	redir_setup(pos, data->cmd_nb, data);
	if (execve(cmd_path, cmd, data->env) == -1 && errno == ENOEXEC)
		execute_script_without_shebang(cmd, data->env);
	ft_printf(SH_NAME": %s: %s", cmd[0], strerror(errno));
	free_list(cmd);
	free_alloc(data);
	exit(EXIT_FAILURE);
}

int	child(char **cmd, t_data *data, int pos)
{
	int		is_builtin;
	char	**path;

	is_builtin = check_builtin(cmd, data);
	if (is_builtin >= 0)
		return (free_list(cmd), is_builtin);
	path = set_path_list(data);
	child_execution(cmd, path, data, pos);
	exit(EXIT_FAILURE);
}

void	father(char **cmd, t_data *data, int pos)
{
	free_list(cmd);
	close(data->pipe_fd[WRITE_END]);
	dup2(data->pipe_fd[READ_END], STDIN_FILENO);
	if (data->process_fd[READ_END] != STDIN_FILENO)
		close(data->process_fd[READ_END]);
	if (data->process_fd[WRITE_END] != STDOUT_FILENO)
		close(data->process_fd[WRITE_END]);
	if (pos == data->cmd_nb)
	{
		dup2(data->tmp_stdio_fd[0], STDIN_FILENO);
		dup2(data->tmp_stdio_fd[1], STDOUT_FILENO);
		close(data->pipe_fd[READ_END]);
	}
}

static int	fork_setup(char **cmd, t_data *data, int pos)
{
	if (pipe(data->pipe_fd) == -1)
		return (-1);
	data->return_val = 0;
	data->max_pid = fork();
	if (data->max_pid == -1)
		return (-1);
	if (data->max_pid == 0)
		child(cmd, data, pos);
	else
	{
		father(cmd, data, pos);
		if (pos == data->cmd_nb)
		{
			dup2(data->tmp_stdio_fd[0], STDIN_FILENO);
			dup2(data->tmp_stdio_fd[1], STDOUT_FILENO);
		}
	}
	return (0);
}

int	executer(t_list *cmd_list, t_data *data)
{
	char	**cmd;
	int		pos;

	//DELETE
	ft_printf(COLOR_CYAN"EXECUTER START\n"COLOR_RESET);
	ft_printf("cmd_number: %d\n\n", data->cmd_nb);
	data->tmp_stdio_fd[0] = dup(STDIN_FILENO);
	data->tmp_stdio_fd[1] = dup(STDOUT_FILENO);
	while (cmd_list)
	{
		pos = cmd_list->cmd_pos;
		if (get_iofiles_fd(data->process_fd, cmd_list, pos) \
			|| get_heredoc_input(cmd_list, pos, data))
			return (-1);
		set_signal_handlers(0);
		cmd = fill_current_cmd(cmd_list, pos, data);
		update_last_executed_cmd(data, cmd);
		if (!cmd || !(*cmd))
			return (-1);
		if (fork_setup(cmd, data, pos) == -1)
			return (-1);
		while (cmd_list && cmd_list->cmd_pos == pos)
			cmd_list = cmd_list->next;
	}
	return (0);
}
