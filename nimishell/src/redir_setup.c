/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-mada <bde-mada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 17:57:29 by bde-mada          #+#    #+#             */
/*   Updated: 2023/11/25 17:47:52 by bde-mada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* int	redir_setup(int pos, int *fd, int cmd_number, int *process_fd, int *pipe_fd, int *tmp_stdio_fd)
{
	if (pos == 0)
	{
		if (process_fd[READ_END] != STDIN_FILENO)
			dup2(process_fd[READ_END], STDIN_FILENO);
		if (process_fd[WRITE_END] == STDOUT_FILENO && cmd_number > 0)
			dup2(pipe_fd[WRITE_END], STDOUT_FILENO);
		else if (process_fd[WRITE_END] != STDOUT_FILENO)
			dup2(process_fd[WRITE_END], STDOUT_FILENO);
	}
	if (pos > 0 && pos == cmd_number)
	{
		close(pipe_fd[WRITE_END]);
		if (process_fd[READ_END] != STDIN_FILENO)
			dup2(process_fd[READ_END], STDIN_FILENO);
		if (process_fd[WRITE_END] == STDOUT_FILENO)
			dup2(tmp_stdio_fd[WRITE_END], STDOUT_FILENO);
		else
			dup2(process_fd[WRITE_END], STDOUT_FILENO);
	}
	else
	{
		if (process_fd[READ_END] == STDIN_FILENO)
			dup2(pipe_fd[READ_END], STDIN_FILENO);
		else
			dup2(process_fd[READ_END], STDIN_FILENO);
		if (process_fd[WRITE_END] != STDOUT_FILENO)
			dup2(process_fd[WRITE_END], STDOUT_FILENO);
	}
} */

static int	redir_pos_0(int *process_fd, int *pipe_fd, int cmd_number)
{
	ft_printf("redirecting first command\n");
	if (process_fd[READ_END] != STDIN_FILENO)
	{
		ft_printf("Process %d input is file %d\n", 0, process_fd[0]);
		if (dup2(process_fd[READ_END], STDIN_FILENO) == -1)
			return (-1);
	}
	if (process_fd[WRITE_END] == STDOUT_FILENO && cmd_number > 0)
	{
		ft_printf("Process %d sending output to pipe\n", 0);
		if (dup2(pipe_fd[WRITE_END], STDOUT_FILENO) == -1)
			return (-1);
	}
	else if (process_fd[WRITE_END] != STDOUT_FILENO)
	{
		ft_printf("Process %d sending output to file %d\n", 0, process_fd[1]);
		if (dup2(process_fd[WRITE_END], STDOUT_FILENO))
			return (-1);
	}
	ft_printf("end redir 0\n", 0);
	return (0);
}

static int	redir_last(int *tmp_stdio_fd, int *process_fd, int *pipe_fd)
{
	ft_printf("redirecting last command\n");
	if (close(pipe_fd[WRITE_END]) == -1)
		return (-1);
	if (process_fd[READ_END] != STDIN_FILENO)
	{
		if (dup2(process_fd[READ_END], STDIN_FILENO) == -1)
			return (-1);
	}
	else if (dup2(pipe_fd[READ_END], STDIN_FILENO) == -1)
		return (-1);
	if (process_fd[WRITE_END] == STDOUT_FILENO)
	{	
		if (dup2(tmp_stdio_fd[WRITE_END], STDOUT_FILENO) == -1)
			return (-1);
	}
	else if (dup2(process_fd[WRITE_END], STDOUT_FILENO) == -1)
		return (-1);
	return (0);
}

static int redir_middle(int *process_fd, int *pipe_fd)
{
	ft_printf("redirecting middle command\n");
	if (process_fd[READ_END] == STDIN_FILENO)
	{
		if (dup2(pipe_fd[READ_END], STDIN_FILENO) == -1)
			return (-1);
	}
	else if (dup2(process_fd[READ_END], STDIN_FILENO) == -1)
		return (-1);
	if (process_fd[WRITE_END] != STDOUT_FILENO)
	{
		if (dup2(process_fd[WRITE_END], STDOUT_FILENO) == -1)
			return (-1);
	}
	else if (dup2(pipe_fd[WRITE_END], STDOUT_FILENO) == -1)
		return (-1);
	return (0);
}

/**
 * @param fd[0] tmp_stdio_fd
 * @param fd[2] process_fd
 * @param fd[4] pipe_fd
  */
int	redir_setup(int pos, int cmd_nb, t_data *data)
{
	//DELETE
	ft_printf("redir_setup, pos: %d, cmd_nb: %d\n", pos, cmd_nb);
	if (pos == 0)
	{
		if (redir_pos_0(data->process_fd, data->pipe_fd, cmd_nb) == -1)
			return (-1);
	}
	else if (pos > 0 && pos == cmd_nb)
	{
		if (redir_last(data->tmp_stdio_fd, data->process_fd, data->pipe_fd) == -1)
			return (-1);
	}
	else if (redir_middle(data->process_fd, data->pipe_fd) == -1)
		return (-1);
	return (0);
}

/* 	if (pos == 0)
	{
		close(pipe_fd[READ_END]);
		if (process_fd[READ_END] == 0)
		{
			ft_printf("Process %d input is stdin\n", pos);
		}
		else
		{
			ft_printf("Process %d input is file %d\n", pos, process_fd[0]);
			dup2(process_fd[READ_END], STDIN_FILENO);
		}
		if (process_fd[WRITE_END] == STDOUT_FILENO && cmd_number > 0)
		{
			ft_printf("Process %d sending output to pipe\n", pos);
			dup2(pipe_fd[WRITE_END], STDOUT_FILENO);
		}
		else if (process_fd[WRITE_END] == STDOUT_FILENO)
		{
			ft_printf("Process %d sending output to terminal\n", pos, process_fd[1]);
			dup2(tmp_stdio_fd[WRITE_END], STDOUT_FILENO);
		}
		else 
		{
			ft_printf("Process %d sending output to file %d\n", pos, process_fd[1]);
			dup2(process_fd[WRITE_END], STDOUT_FILENO);
		}
	}
	else if (pos == cmd_number && cmd_number > 0)
	{
		close(pipe_fd[WRITE_END]);
		if (process_fd[READ_END] == 0)
		{	
			ft_printf("Process %d input is pipe\n", pos);
//			dup2(pipe_fd[READ_END], STDIN_FILENO);
		}
		else
		{
			dup2(process_fd[READ_END], STDIN_FILENO);
		}
		if (process_fd[WRITE_END] == STDOUT_FILENO)
		{
			ft_printf("Process %d sending output to stdout\n", pos);
			dup2(tmp_stdio_fd[1], STDOUT_FILENO);	
		}
		else
		{
			ft_printf("Process %d sending output to file %d\n", pos, process_fd[1]);
			dup2(process_fd[WRITE_END], STDOUT_FILENO);
		}
	}
	else
	{
		if (process_fd[WRITE_END] == STDOUT_FILENO)
		{
			dup2(pipe_fd[WRITE_END], STDOUT_FILENO);
		}
		else
		{
			dup2(process_fd[WRITE_END], STDOUT_FILENO);
		}
		if (process_fd[READ_END] == STDIN_FILENO)
		{
//			dup2(pipe_fd[READ_END], STDIN_FILENO);
		}
		else
		{
			dup2(process_fd[READ_END], STDIN_FILENO);
		}
	} */
