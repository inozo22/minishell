/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-mada <bde-mada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:48:44 by bde-mada          #+#    #+#             */
/*   Updated: 2023/12/07 15:59:32 by bde-mada         ###   ########.fr       */
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

char	**set_path_list(t_data *data)
{
	int		i;
	char	**path;

	i = -1;
	path = NULL;
	while (data->env[++i])
	{
		if (!ft_strncmp(data->env[i], "PATH=", 5))
		{
			path = ft_split(data->env[i] + 5, ':');
			if (!path)
				errors(ENOMEM, data);
			break ;
		}
	}
	return (path);
}

static char	*expand_file(char *file, int type, t_data *data)
{
	int		i[3];
	char	*string;

	string = file;
	ft_bzero(i, 3 * sizeof(int));
	if (type == REDIR_IN || type == REDIR_OUT)
		string = expander(file, data, i);
	return (string);
}

/**
 * @author bde-mada
 */
int	get_iofiles_fd(int *fd, t_list *lst, int pos, t_data *data)
{
	char	*file_name;

	while (lst && lst->cmd_pos == pos)
	{
		file_name = expand_file(lst->content, lst->type, data);
		if (!file_name || !*file_name)
			return (error_msg(lst->content, 5));
		if (lst->type == REDIR_IN)
		{
			if (fd[0] != STDIN_FILENO)
				close(fd[0]);
			fd[0] = open(file_name, O_RDONLY);
		}
		if ((lst->type == REDIR_OUT || lst->type == APPEND) && fd[1] != 1)
			close(fd[1]);
		if (lst->type == REDIR_OUT)
			fd[1] = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (lst->type == APPEND)
			fd[1] = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd[0] == -1 || fd[1] == -1)
			return (close_files_if_error(fd, file_name));
		lst = lst->next;
	}
	return (0);
}
