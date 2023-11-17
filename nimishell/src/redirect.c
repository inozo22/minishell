/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-mada <bde-mada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 19:31:19 by bde-mada          #+#    #+#             */
/*   Updated: 2023/06/17 19:31:19 by bde-mada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <sys/wait.h>

int	heredoc_to_stdin(char *input)
{
	pid_t	pid;
	int		fd[2];

	if (!input || pipe(fd) == -1)
		return (1);
	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		close(fd[READ_END]);
		write(fd[WRITE_END], input, ft_strlen(input));
		close(fd[WRITE_END]);
		exit(0);
	}
	wait(NULL);
	close(fd[WRITE_END]);
	dup2(fd[READ_END], STDIN_FILENO);
	close(fd[READ_END]);
	return (0);
}

/* int	heredoc_read(char *eof, char **envp, pid_t pid)
{
	char	*line_read;
	char	*input;
	char	*tmp;

	input = NULL;
	line_read = NULL;
	g_return_val = -1;
	while (g_return_val < 0)
	{
		line_read = readline(">");
		if (!line_read || !ft_strcmp(eof, line_read))
			break ;
		line_read = expander(line_read, envp, pid);
		tmp = input;
		input = ft_strjoin_many(3, input, "\n", line_read);
		free(tmp);
		del((void **)&line_read);
	}
	del((void **)&line_read);
	return (heredoc_to_stdin(input));
} */

/**
 * @note 231117nimai: I think it's accetable leave g_return_val here although with new correction. 
  */
int	heredoc_read(char *eof, t_data *data)
{
	char	*line_read;
	char	*input;
	char	*tmp;

	input = NULL;
	line_read = NULL;
	g_return_val = -1;
	while (g_return_val < 0)
	{
		line_read = readline(">");
		if (!line_read || !ft_strcmp(eof, line_read))
			break ;
		line_read = expander(line_read, data, 0);
		tmp = input;
		input = ft_strjoin_many(3, input, "\n", line_read);
		free(tmp);
		del((void **)&line_read);
	}
	del((void **)&line_read);
	return (heredoc_to_stdin(input));
}

void	redir_setup(int pos, int cmd_number, int *process_fd, int *pipe_fd, int *tmp_stdio_fd)
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
	else if (pos > 0 && pos == cmd_number)
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
		if (process_fd[READ_END] != STDIN_FILENO)
			dup2(process_fd[READ_END], STDIN_FILENO);
		if (process_fd[WRITE_END] != STDOUT_FILENO)
			dup2(process_fd[WRITE_END], STDOUT_FILENO);
		else
			dup2(pipe_fd[WRITE_END], STDOUT_FILENO);
	}
}
