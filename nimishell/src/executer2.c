/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-mada <bde-mada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 12:18:50 by bde-mada          #+#    #+#             */
/*   Updated: 2023/09/20 19:34:39 by bde-mada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

/**
 * @author bde-mada
 */
char	**fill_current_cmd(t_list *lst, int pos, char **envp, pid_t pid)
{
	char	**cmd;
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = lst;
	while (tmp && tmp->cmd_pos == pos)
	{
		if (tmp->type == WORD || tmp->type == PIPE_LINE)
			++i;
		tmp = tmp->next;
	}
	if (!i)
		return (NULL);
	cmd = (char **)ft_calloc(i + 1, sizeof(char *));
	if (!cmd)
		return (NULL);
	i = -1;
	while (lst && lst->cmd_pos == pos)
	{
		if (lst->type == WORD || lst->type == PIPE_LINE)
			cmd[++i] = expander(lst->content, envp, pid);
		lst = lst->next;
	}
	return (cmd);
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
//	ft_printf("Output in get_iofiles in pos %d: fd[0]: %d, fd[1]: %d\n", pos, fd[0], fd[1]);

int	get_heredoc_input(t_list *lst, int pos, char **envp, pid_t pid)
{
	char	*tmp_eof;

	tmp_eof = NULL;
	while (lst && lst->cmd_pos == pos)
	{
		if (lst->type == HERE_DOC)
			tmp_eof = lst->content;
		lst = lst->next;
	}
	if (tmp_eof && heredoc_read(tmp_eof, envp, pid))
		return (1);
	return (0);
}

int	child_execution(char **cmd, char **env, char **path, t_data *data, int pos, int cmd_number, int *process_fd, int *pipe_fd, int *tmp_stdio_fd)
{
	char	*cmd_path;
	int		return_val;
	
	//child
	return_val = 0;
	cmd_path = get_cmd_path(cmd[0], path, &return_val);
	ft_printf("Return val from get_cmd_path: %d\n", return_val);
	if (!cmd_path)
	{
		return_val = error_msg(cmd[0], return_val);
		free_list(cmd);
		free_alloc(data);
		exit(return_val);
	}
	redir_setup(pos, cmd_number, process_fd, pipe_fd, tmp_stdio_fd);
	if (execve(cmd_path, cmd, env) == -1 && errno == ENOEXEC)
		execute_script_without_shebang(cmd, env);
		
	//as doesn't return when execute the command well, there is no protection
	ft_printf(SHELL_NAME": %s: %s", cmd[0], strerror(errno));
	//free all the data if execve fails
	//230809nimai: comment free to avoid double freeing.
//		free(cmd_path);
	free_list(cmd);
	free_alloc(data);		
	exit(1);
}

int	executer(t_list *lst, int cmd_number, \
				char **path, char **env, t_data *data)
{
	int		tmp_stdio_fd[2];
	pid_t	pid;
	int		process_fd[2];
	int		e_status;
	int		pos;
	char	**cmd;
	int		pipe_fd[2];
	int		max_pid;

	e_status = 0;
	tmp_stdio_fd[0] = dup(STDIN_FILENO);
	tmp_stdio_fd[1] = dup(STDOUT_FILENO);
	pos = 0;
	max_pid = 0;
	//set the initial input
/* 	if (infile)
		fdin = open(infile, O_RDONLY);
	else
	{
		// Use default input
		fdin = dup(tmp_stdio_fd[0]);
	} */
	// IMPORTANTE: check if the last command is exit
/* 	if (ft_strcmp(cmd[cmd_number - 1][0], "exit"))
		return (0); */
	ft_printf(COLOR_ACCENT"EXECUTER START\n"COLOR_RESET);
	if (lst)
		ft_printf("lst_content: %s\n", lst->content);
	while (lst)
	{
		cmd = NULL;
		ft_printf("Current cmd pos: %d, cmd_number: %d\n", lst->cmd_pos, cmd_number);
		if (lst->cmd_pos == pos)
		{
			if (get_iofiles_fd(process_fd, lst, pos) == 0 \
				&& get_heredoc_input(lst, pos, data->env, data->pid) == 0)
			{
				ft_printf("FDs set\n");
				if (pipe(pipe_fd) == -1)
					return (-1);
				//set singnal handlers for child process
				set_signal_handlers(0);
				cmd = fill_current_cmd(lst, pos, data->env, data->pid);
				if (!cmd || !(*cmd))
				{	
					if (lst->cmd_pos == cmd_number)
						break ;
					else
						continue ;
				}

				int	j = -1;
				while (cmd[++j])
					ft_printf("cmd[%d] = %s\n", j, cmd[j]);
				ft_printf("\n");
				g_return_val = 0;
				int is_builtin = check_builtin(cmd, data);
				ft_printf("\nCheck builtin return: %d\n", is_builtin);
				if (is_builtin >= 0)
					return (free(cmd), is_builtin);

				// Create child process
				pid = fork();
				if (pid == -1)
					return (-1);
				if (pid == 0)
					child_execution(cmd, env, path, data, pos, cmd_number, process_fd, pipe_fd, tmp_stdio_fd);
				close(pipe_fd[WRITE_END]);
				dup2(pipe_fd[READ_END], STDIN_FILENO);
//				close(pipe_fd[READ_END]);
				
				if (pid > max_pid)
					max_pid = pid;
				if (process_fd[READ_END] != STDIN_FILENO)
					close(process_fd[READ_END]);
				if (process_fd[WRITE_END] != STDOUT_FILENO)
					close(process_fd[WRITE_END]);
				if (pos == cmd_number)
				{	
					dup2(tmp_stdio_fd[0], STDIN_FILENO);
					dup2(tmp_stdio_fd[1], STDOUT_FILENO);
				}
			}
		}
		while (lst && lst->cmd_pos == pos)
			lst = lst->next;
		pos++;
		free(cmd);
	}
	//for
	//restore in/out defaults
	dup2(tmp_stdio_fd[0], STDIN_FILENO);
	dup2(tmp_stdio_fd[1], STDOUT_FILENO);
	close(tmp_stdio_fd[0]);
	close(tmp_stdio_fd[1]);
	close(pipe_fd[READ_END]);
	close(pipe_fd[WRITE_END]);
	int wait_ret;
	while (1)
	{
		wait_ret = waitpid(-1, &e_status, WUNTRACED);
		if (wait_ret == max_pid)
			g_return_val = check_exit_status(e_status);
		cmd_number--;
		if (cmd_number < 0)
			break ;
	}
//	waitpid(pid, &e_status, WUNTRACED);
	return (0);
}
