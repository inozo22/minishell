/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-mada <bde-mada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:03:23 by bde-mada          #+#    #+#             */
/*   Updated: 2023/12/10 16:55:32 by bde-mada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

int	set_fds(t_data *data, int mode)
{
	if (!mode)
	{
		data->tmp_stdio_fd[0] = dup(STDIN_FILENO);
		data->tmp_stdio_fd[1] = dup(STDOUT_FILENO);
		if (data->tmp_stdio_fd[0] == -1 || data->tmp_stdio_fd[1] == -1)
			return (perror(SH_NAME), 1);
	}
	if (mode)
	{
		data->process_fd[0] = dup(data->tmp_stdio_fd[0]);
		data->process_fd[1] = dup(data->tmp_stdio_fd[1]);
		if (data->process_fd[0] == -1 || data->process_fd[1] == -1)
			return (perror(SH_NAME), 1);
		dup2(data->process_fd[WRITE_END], STDOUT_FILENO);
		close(data->process_fd[WRITE_END]);
		dup2(data->process_fd[READ_END], STDIN_FILENO);
		close(data->process_fd[READ_END]);
	}
	return (0);
}

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
	if (!access(cmd, F_OK) || cmd[0] == '/' || !ft_strncmp(cmd, "./", 2))
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

	wait_ret = -1;
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
