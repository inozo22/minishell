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

int	here_doc_to_stdin(char *input)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
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
	close(fd[WRITE_END]);
	dup2(fd[READ_END], STDIN_FILENO);
	close(fd[READ_END]);
	return (0);
}

int	here_doc_read(char *eof)
{
	char	*line_read;
	char	*input;
	char	*tmp;

	input = NULL;
	while (1)
	{
		line_read = readline(">");
		if (ft_strcmp(eof, line_read))
			break ;
		tmp = input;
		input = ft_strjoin(line_read, input);
		free(tmp);
		del((void **)&line_read);
	}
	del((void **)&line_read);
	return (here_doc_to_stdin(input));
}

int	redir(char **command)
{
	if (command[0][0] == '>')
		return (open(command[1], O_WRONLY | O_CREAT | O_TRUNC, 0644));
	else if (ft_strncmp(command[0], ">>", 2))
		return (open(command[1], O_WRONLY | O_CREAT | O_APPEND, 0644));
	else if (command[0][0] == '<')
		return (open(command[1], O_RDONLY));
	else if (ft_strncmp(command[0], "<<", 2))
		return (here_doc_read(command[1]));
	return (-1);
}
