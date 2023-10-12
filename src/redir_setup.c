/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-mada <bde-mada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 17:57:29 by bde-mada          #+#    #+#             */
/*   Updated: 2023/09/20 18:49:07 by bde-mada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
 
int	redir_setup(int pos, int *fd, int cmd_number, int *process_fd, int *pipe_fd, int *tmp_stdio_fd)
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
		close(pipe_fd[WRITE_END])
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
