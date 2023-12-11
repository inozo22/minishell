/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:48:44 by bde-mada          #+#    #+#             */
/*   Updated: 2023/12/11 12:18:22 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

int	execute_script_without_shebang(char **cmd, char **env)
{
	char	*new_argv[2];

	new_argv[0] = cmd[0];
	new_argv[1] = NULL;
	free_list(cmd);
	if (execve("/bin/bash", new_argv, env) == -1)
		return (1);
	return (0);
}

int	close_files_if_error(int fd[2], char *file_name)
{
	error_file(file_name);
	if (fd[0] != -1 && fd[0] != STDIN_FILENO)
		close(fd[0]);
	if (fd[1] != -1 && fd[1] != STDOUT_FILENO)
		close(fd[1]);
	return (1);
}

static int	set_iofiles_redir(int type, int *fd, char *file_name)
{
	if (type == REDIR_IN)
	{
		fd[0] = open(file_name, O_RDONLY);
		if (dup2(fd[0], STDIN_FILENO) == -1)
			return (1);
	}
	if (type == REDIR_OUT)
	{
		fd[1] = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			return (1);
	}
	if (type == APPEND)
	{
		fd[1] = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			return (1);
	}
	return (0);
}

static char	*expand_file(char *file, int type, t_data *data)
{
	int		i[3];
	char	*string;

	string = file;
	ft_bzero(i, 3 * sizeof(int));
	if (type == REDIR_IN || type == REDIR_OUT)
	{
		string = expander(file, data, i);
		free (file);
	}
	return (string);
}

int	get_iofiles_fd(int *fd, t_list *lst, int pos, t_data *data)
{
	char	*file_name;

	while (lst && lst->cmd_pos == pos)
	{
		file_name = expand_file(ft_strdup(lst->content), lst->type, data);
		if (!file_name || !*file_name)
			return (error_msg(lst->content, 5));
		if (set_iofiles_redir(lst->type, fd, file_name))
			return (close_files_if_error(fd, file_name));
		lst = lst->next;
		free(file_name);
	}
	return (0);
}

/**
 * @author bde-mada
 */
/* int	get_iofiles_fd(int *fd, t_list *lst, int pos, t_data *data)
{
	char	*file_name;

	while (lst && lst->cmd_pos == pos)
	{
		file_name = expand_file(ft_strdup(lst->content), lst->type, data);
		if (!file_name || !*file_name)
			return (error_msg(lst->content, 5));
		if (lst->type == REDIR_IN)
		{
			fd[0] = open(file_name, O_RDONLY);
			dup2(fd[0], STDIN_FILENO);
		}
		if (lst->type == REDIR_OUT)
		{
			fd[1] = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			dup2(fd[1], STDOUT_FILENO);
		}
		if (lst->type == APPEND)
		{
			fd[1] = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
			dup2(fd[1], STDOUT_FILENO);
		}
		if (fd[0] == -1 || fd[1] == -1)
			return (close_files_if_error(fd, file_name));
		lst = lst->next;
		free(file_name);
	}
	return (0);
} */
