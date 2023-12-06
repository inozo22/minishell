/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-mada <bde-mada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:48:44 by bde-mada          #+#    #+#             */
/*   Updated: 2023/12/06 17:07:49 by bde-mada         ###   ########.fr       */
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



/**
 * @author bde-mada
 */
int	get_iofiles_fd(int *fd, t_list *lst, int pos)
{
	fd[0] = STDIN_FILENO;
	fd[1] = STDOUT_FILENO;
	while (lst && lst->cmd_pos == pos)
	{
		if (lst->type == REDIR_IN)
		{
			if (fd[0] != STDIN_FILENO)
				close(fd[0]);
			fd[0] = open(lst->content, O_RDONLY);
		}
		if ((lst->type == REDIR_OUT || lst->type == APPEND) \
				&& fd[1] != STDOUT_FILENO)
			close(fd[1]);
		if (lst->type == REDIR_OUT)
			fd[1] = open(lst->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (lst->type == APPEND)
			fd[1] = open(lst->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd[0] == -1 || fd[1] == -1)
			return (close_files_if_error(fd, lst->content));
		lst = lst->next;
	}
	return (0);
}
