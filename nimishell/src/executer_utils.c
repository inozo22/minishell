/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-mada <bde-mada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:48:44 by bde-mada          #+#    #+#             */
/*   Updated: 2023/11/24 19:10:26 by bde-mada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

int	check_is_directory(char *cmd)
{
	struct stat	t_stat;

	if (!stat(cmd, &t_stat) && S_ISDIR(t_stat.st_mode))
	{
		if (cmd[0] == '/' || cmd[ft_strlen(cmd) - 1] == '/')
			return (3);
		else
			return (1);
	}
	return (0);
}

/**
 * @author bde-mada
 * @param path[0] = tmp_path
 * @param path[1] = cmd_path
*/
char	*get_cmd_path(char *cmd, char **path, int *return_val)
{
	int			i;
	char		*cmd_path[2];

	i = -1;
	ft_bzero(cmd_path, 2 * sizeof(char *));
	*return_val = check_is_directory(cmd);
	if (*return_val)
		return (NULL);
	if (!access(cmd, F_OK))
		return (cmd);
	while (path && path[++i])
	{
		cmd_path[0] = ft_strjoin(path[i], "/");
		if (cmd_path[0] && cmd)
			cmd_path[1] = ft_strjoin(cmd_path[0], cmd);
		free(cmd_path[0]);
		if (!access(cmd_path[1], F_OK))
			break ;
		free(cmd_path[1]);
		cmd_path[1] = NULL;
	}
	if (!cmd_path[1])
		*return_val = 1;
	return (cmd_path[1]);
}
//	ft_printf("cmd_path: %s\n\n", cmd_path[1]);

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

/**
 * @note 230811nimai: add g_return_val, check if there is another way to
 * reset g_return_val
 */
/* 	if ((g_return_val == 130 || g_return_val == 131) && WIFEXITED(e_status))
		return (WEXITSTATUS(e_status));
	else if (g_return_val)
		return (g_return_val); */
void	get_exit_status(t_data *data)
{
	int wait_ret;
	int e_status;
	
	while (1)
	{
		wait_ret = waitpid(-1, &e_status, WUNTRACED);
		if (wait_ret == data->max_pid)
		{
			if (g_return_val == 1)
				data->return_val = g_return_val;
			if (WIFSIGNALED(e_status))
				data->return_val = 128 + WTERMSIG(e_status);
			if (WIFEXITED(e_status))
				data->return_val = WEXITSTATUS(e_status);
		}
		if (data->cmd_nb-- < 0)
			break ;
	}
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
