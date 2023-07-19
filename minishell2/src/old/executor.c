/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-mada <bde-mada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 23:43:32 by bde-mada          #+#    #+#             */
/*   Updated: 2023/07/12 16:00:24 by bde-mada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cmd_path(char *cmd, char **path)
{
	int		i;
	char	*cmd_path;
	char	*tmp_path;

	i = -1;
	tmp_path = NULL;
	if (!access(cmd, F_OK))
		return (cmd);
	while (path && path[++i])
	{
		tmp_path = ft_strjoin(path[i], "/");
		if (tmp_path && cmd)
			cmd_path = ft_strjoin(tmp_path, cmd);
		free(tmp_path);
		if (!access(cmd_path, F_OK))
			break ;
		del((void **)&(cmd_path));
	}
	ft_printf("cmd_path: %s\n", cmd_path);
	return (cmd_path);
}

void	execute(char *cmd_path, char **cmd, char **envp)
{
	if (execve(cmd_path, cmd, envp) == -1)
	{
		error_msg("minishell", cmd[0], 1);
//		if (errno == 13 && !last)
//			errors(0, param);
//		else
//			errors(8, param);
		exit(1);
	} 
}

int	exit_child(t_data *data, int *fd_pipe, char ***cmd)
{
	del_array((void ***)&data->env);
	del_array((void ***)&data->path);
	close(fd_pipe[WRITE_END]);
	error_msg("minishell: ", *cmd[0], 1);
	errno = 2;
	del_array((void ***)cmd);
	exit(127);
}

static void	execute_child(int *fd_pipe, t_data *data, char **cmd, int redir)
{
	char	*cmd_path;
	
	close(fd_pipe[READ_END]);
	if (redir)
		dup2(fd_pipe[WRITE_END], STDOUT_FILENO);
	ft_printf("I'm in child\n");
	cmd_path = get_cmd_path(cmd[0], data->path);
	if (!cmd_path)
		exit_child(data, fd_pipe, &cmd);
	execute(cmd_path, cmd, data->env);
}

static int	execute_father(int *fd_pipe, int redir)
{
	int		exit_status;
	int		alt_fd;

	exit_status = 0;
	close(fd_pipe[WRITE_END]);
	if (redir)
	{
		alt_fd = dup(STDIN_FILENO);
		dup2(fd_pipe[READ_END], alt_fd);
		close(alt_fd);
	}
	close(fd_pipe[READ_END]);
// 	else
//	{
//		alt_fd = dup(STDOUT_FILENO);
//		dup2(fd_pipe[READ_END], alt_fd);
//	}
	waitpid(0, &exit_status, 0);
//	if (!WIFEXITED(exit_status))
//		errors(38, param);
//	if (WIFEXITED(exit_status) && WEXITSTATUS(exit_status))
//		errors(exit_status, param);
	ft_printf("I'm in father\n");
	return (exit_status);
}

int	child_creation(t_data *data, char **cmd)
{
	int		fd_pipe[2];
	pid_t	pid;
	
//Check to disable:
	if (!cmd)
		return (0);
//Actual function:
	if (pipe(fd_pipe) == -1)
		return (1);
	ft_printf("Hey\n");
	pid = fork();
	if (pid == -1)
	{
//		close(param->fd_in);
//		close(param->fd_out);
		close(fd_pipe[READ_END]);
		close(fd_pipe[WRITE_END]);
		return (2);
	}
	if (pid == 0)
		execute_child(fd_pipe, data, cmd, 0);
	else
		wait(NULL);
		data->return_val = execute_father(fd_pipe, 0);
	return (0);
}
