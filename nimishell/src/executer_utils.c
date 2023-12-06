/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-mada <bde-mada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:48:44 by bde-mada          #+#    #+#             */
/*   Updated: 2023/12/06 16:12:12 by bde-mada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int	wait_ret;
	int	e_status;

	while (1)
	{
		if (g_return_val == 1)
		{
			data->return_val = g_return_val;
			break ;
		}
		wait_ret = waitpid(-1, &e_status, WUNTRACED);
		if (wait_ret == data->max_pid)
		{
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
