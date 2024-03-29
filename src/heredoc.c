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
#include <sys/wait.h>

int	heredoc_to_stdin(char *input)
{
	pid_t	pid;
	int		fd[2];
	char	*tmp;

	tmp = input;
	input = ft_strjoin(input, "\n");
	free(tmp);
	if (!input || pipe(fd) == -1)
		return (1);
	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		close(fd[READ_END]);
		write(fd[WRITE_END], input, ft_strlen(input));
		free(input);
		close(fd[WRITE_END]);
		exit(0);
	}
	wait(NULL);
	close(fd[WRITE_END]);
	dup2(fd[READ_END], STDIN_FILENO);
	close(fd[READ_END]);
	return (free(input), 0);
}

void	free_strings(char **list)
{
	free(list[0]);
	free(list[1]);
	free(list[2]);
	list[0] = NULL;
	list[1] = NULL;
	list[2] = NULL;
	free(list);
}

/**
 * @note 231117nimai: I think it's accetable leave g_return_val 
 * 		here although with new correction.
 * @param strings[0] = gnl input
 * @param strings[1] = expanded
 * @param strings[2] = tmp input
  */
char	*heredoc_read(char *eof, t_data *data, char **input)
{
	char	**strings;
	int		i[3];

	ft_bzero(i, 3 * sizeof(int));
	while (1)
	{
		strings = ft_calloc(3, sizeof(char *));
		if (g_return_val == 1)
			return (free_strings(strings), NULL);
		write(1, "> ", 2);
		strings[0] = get_next_line(STDIN_FILENO, 0);
		if (strings[0])
			strings[0][ft_strlen(strings[0]) - 1] = '\0';
		if (!strings[0] || !ft_strcmp(eof, strings[0]))
			break ;
		strings[1] = expander(strings[0], data, i);
		strings[2] = *input;
		if (!(*input) && strings[1])
			*input = ft_strdup(strings[1]);
		else
			*input = ft_strjoin_many(3, *input, "\n", strings[1]);
		free_strings(strings);
	}
	return (free_strings(strings), get_next_line(STDIN_FILENO, 1), *input);
}

int	get_heredoc_input(t_list *lst, int pos, t_data *data)
{
	char	*input;

	input = NULL;
	while (lst && lst->cmd_pos == pos)
	{
		if (lst->type == HERE_DOC)
		{
			data->process_fd[READ_END] = dup(data->tmp_stdio_fd[READ_END]);
			dup2(data->process_fd[READ_END], STDIN_FILENO);
			close(data->process_fd[READ_END]);
			data->process_fd[WRITE_END] = dup(data->tmp_stdio_fd[WRITE_END]);
			dup2(data->process_fd[WRITE_END], STDOUT_FILENO);
			close(data->process_fd[WRITE_END]);
			free(input);
			set_signal_handlers(1);
			if (!heredoc_read(lst->content, data, &input) || !input)
				return (1);
		}
		lst = lst->next;
	}
	if (input && heredoc_to_stdin(input))
		return (1);
	set_signal_handlers(0);
	return (0);
}
