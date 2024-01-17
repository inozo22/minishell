/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-mada <bde-mada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 17:57:29 by bde-mada          #+#    #+#             */
/*   Updated: 2023/12/10 19:26:53 by bde-mada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* static int	redir_pos_0(int *process_fd, int *pipe_fd, int cmd_nb)
{
	if (process_fd[READ_END] != STDIN_FILENO)
	{
		if (dup2(process_fd[READ_END], STDIN_FILENO) == -1)
			return (-1);
	}
	if (process_fd[WRITE_END] == STDOUT_FILENO && cmd_nb > 0)
	{
		if (dup2(pipe_fd[WRITE_END], STDOUT_FILENO) == -1)
			return (-1);
	}
	else if (process_fd[WRITE_END] != STDOUT_FILENO)
	{
		if (dup2(process_fd[WRITE_END], STDOUT_FILENO))
			return (-1);
	}
	return (0);
}

static int	redir_last(int *tmp_stdio_fd, int *process_fd, int *pipe_fd)
{
	if (close(pipe_fd[WRITE_END]) == -1)
		return (-1);
	if (process_fd[READ_END] == -1)
	{
		if (dup2(tmp_stdio_fd[READ_END], STDIN_FILENO) == -1)
			return (-1);
	}
	if (process_fd[READ_END] != STDIN_FILENO)
	{
		if (dup2(process_fd[READ_END], STDIN_FILENO) == -1)
			return (-1);
	}
	if (process_fd[WRITE_END] == STDOUT_FILENO)
	{
		if (dup2(tmp_stdio_fd[WRITE_END], STDOUT_FILENO) == -1)
			return (-1);
	}
	else if (dup2(process_fd[WRITE_END], STDOUT_FILENO) == -1)
		return (-1);
	return (0);
}

static int	redir_middle(int *tmp_stdio_fd, int *process_fd, int *pipe_fd)
{
	if (process_fd[READ_END] == -1)
	{
		if (dup2(tmp_stdio_fd[READ_END], STDIN_FILENO) == -1)
			return (-1);
	}
	if (process_fd[READ_END] != STDIN_FILENO)
	{
		if (dup2(process_fd[READ_END], STDIN_FILENO) == -1)
			return (-1);
	}
	if (process_fd[WRITE_END] != STDOUT_FILENO)
	{
		if (dup2(process_fd[WRITE_END], STDOUT_FILENO) == -1)
			return (-1);
	}
	else if (dup2(pipe_fd[WRITE_END], STDOUT_FILENO) == -1)
		return (-1);
	return (0);
}*/

/**
 * @param fd[0] tmp_stdio_fd
 * @param fd[2] process_fd
 * @param fd[4] pipe_fd
  */
/* int	redir_setup(int pos, int cmd_nb, t_data *data)
{
	if (pos == 0)
	{
		if (redir_pos_0(data->process_fd, data->pipe_fd, cmd_nb) == -1)
			return (-1);
	}
	else if (pos > 0 && pos == cmd_nb)
	{
		if (redir_last(data->tmp_stdio_fd, \
						data->process_fd, data->pipe_fd) == -1)
			return (-1);
	}
	else if (redir_middle(data->tmp_stdio_fd, \
						data->process_fd, data->pipe_fd) == -1)
		return (-1);
	return (0);
}  */

int	redir_setup(t_data *data, int pos)
{
	if (pos == 0 && data->cmd_nb >= 1)
	{
		if (dup2(data->pipe_fd[WRITE_END], STDOUT_FILENO) == -1 \
			|| close(data->pipe_fd[WRITE_END]) == -1)
			return (perror(SH_NAME), -1);
	}
	else if (pos > 0 && pos < data->cmd_nb)
	{
		if (dup2(data->pipe_fd[WRITE_END], STDOUT_FILENO) == -1 \
			|| close(data->pipe_fd[WRITE_END]) == -1)
			return (perror(SH_NAME), -1);
	}
	else if (pos == data->cmd_nb)
	{
		data->process_fd[1] = dup(data->tmp_stdio_fd[1]);
		if (dup2(data->process_fd[WRITE_END], STDOUT_FILENO) == -1 \
			|| close(data->process_fd[WRITE_END]) == -1)
			return (perror(SH_NAME), -1);
	}
	return (0);
}
