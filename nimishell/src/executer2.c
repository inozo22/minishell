/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-mada <bde-mada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 12:18:50 by bde-mada          #+#    #+#             */
/*   Updated: 2023/09/18 15:52:39 by bde-mada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

char	*get_cmd_path(char *cmd, char **path)
{
	int		i;
	char	*cmd_path;
	char	*tmp_path;

	i = -1;
	tmp_path = NULL;
	cmd_path = NULL;
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
		free(cmd_path);
		cmd_path = NULL;
	}
	//DELETE
	ft_printf("cmd_path: %s\n\n", cmd_path);
	return (cmd_path);
}

/**
 * @note 230811nimai: add g_return_val, check if there is another way to
 * reset g_return_val
 */
int	check_exit_status(int e_status)
{
/* 	if ((g_return_val == 130 || g_return_val == 131) && WIFEXITED(e_status))
		return (WEXITSTATUS(e_status));
	else if (g_return_val)
		return (g_return_val); */
	if (g_return_val == 1)
		return (g_return_val);
	if (WIFSIGNALED(e_status))
		return (128 + WTERMSIG(e_status));
	if (WIFEXITED(e_status))
		return (WEXITSTATUS(e_status));
	return (0);
}

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

/**
 * @param tmp_stdfd[0] = tmp_stdin
 * @param tmp_stdfd[1] = tmp_stdout
 * @param fdin[0] = fdin
 * @param fdin[1] = fdout
*/
/* int executer(char *infile, char *outfile, t_list *lst, int cmd_number,
				char **path, char **env, t_data *data)
{
	//save in/out
	int tmp_stdin;
	int tmp_stdout;
	pid_t pid;
	int fdin;
	int fdout;
	int e_status;
	int i;

	e_status = 0;
	tmp_stdin = dup(STDIN_FILENO);
	tmp_stdout = dup(STDOUT_FILENO);
	i = -1;
	//set the initial input
	if (infile)
		fdin = open(infile, O_RDONLY);
	else
	{
		// Use default input
		fdin = dup(tmp_stdin);
	}
	// IMPORTANTE: check if the last command is exit
// 	if (ft_strcmp(cmd[cmd_number - 1][0], "exit"))
//		return (0);
	while (lst && (lst->type == WORD || lst->type == PIPE_LINE))
//	while (++i < cmd_number)
	{
		++i;
		if (lst->type == WORD || lst->type == PIPE_LINE)
		{
			
			//redirect input
			dup2(fdin, 0);
			close(fdin);
			//setup output
			if(i == cmd_number)
			{
				// Last simple command
				if(outfile)
					fdout = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				else
				{
					// Use default output 
					fdout = dup(tmp_stdout);
				}
			}
			else
			{
				// Not last
				//simple command 
				//create pipe
				int fdpipe[2];
				pipe(fdpipe);
				fdout = fdpipe[1];
				fdin = fdpipe[0];
			}
			// if/else
			// Redirect output
			dup2(fdout,1);
			close(fdout);
			//set singnal handlers for child process
			set_signal_handlers(0);
			printf("cmd[i][0] = %s\n", lst->content);
			char **cmd = ft_calloc(2, sizeof(char *));
			cmd[0] = lst->content;
			int is_builtin = check_builtin(cmd, data);
			ft_printf("Check builtin return: %d\n", is_builtin);
			if (is_builtin >= 0)
				return (is_builtin);
			
			// Create child process
			pid = fork();
			if (pid == 0)
			{
				//child
				char *cmd_path = NULL;
				cmd_path = get_cmd_path(lst->content, path);
				update_last_executed_cmd(data, cmd_path);
				if (execve(cmd_path, cmd, env) == -1 && errno == ENOEXEC)
					execute_script_without_shebang(cmd, env);
				//as doesn't return when execute the command well, there is no protection
				perror("execve");
				//free all the data if execve fails
				//230809nimai: comment free to avoid double freeing.
				//free(cmd_path);
				exit(1);
			}
		}
		lst = lst->next;
	}
	//for
	//restore in/out defaults
	dup2(tmp_stdin, 0);
	dup2(tmp_stdout, 1);
	close(tmp_stdin);
	close(tmp_stdout);

	wait(&e_status);
//	waitpid(pid, &e_status, WUNTRACED);
	return (check_exit_status(e_status));
}
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
	tmp = lst;
	while (tmp && tmp->cmd_pos == pos)
	{
		if (tmp->type == WORD || tmp->type == PIPE_LINE)
			cmd[++i] = expander(tmp->content, envp, pid);
		tmp = tmp->next;
	}
	cmd[++i] = NULL;
	return (cmd);
}

/**
 * @note protect function open
 * 
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
			ft_printf("Opening input file: %s\n", lst->content);
			fd[0] = open(lst->content, O_RDONLY);
		}
		if (fd[0] == -1)
		{
			if (fd[1] != STDOUT_FILENO)
				close(fd[1]);
			return (1);
		}
		if (lst->type == REDIR_OUT)
		{
			if (fd[1] != STDOUT_FILENO)
				close(fd[1]);
			ft_printf("Opening output file: %s\n", lst->content);
			fd[1] = open(lst->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		}
		if (lst->type == APPEND)
		{
			if (fd[1] != STDOUT_FILENO)
				close(fd[1]);
			ft_printf("Opening output file: %s\n", lst->content);
			fd[1] = open(lst->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
		}
		if (fd[1] == -1)
		{
			if (fd[0] != STDIN_FILENO)
				close (fd[0]);
			return (1);
		}
		lst = lst->next;
	}
	ft_printf("Output in get_iofiles in pos %d: fd[0]: %d, fd[1]: %d\n", pos, fd[0], fd[1]);
	return (0);
}

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
	cmd_path = get_cmd_path(cmd[0], path);
	if (!cmd_path)
	{
		return_val = error_msg(SHELL_NAME, cmd[0], 1);
		free_list(cmd);
		free_alloc(data);
		exit(return_val);
	}
	if (pos == 0)
	{
		close(pipe_fd[READ_END]);
		if (process_fd[READ_END] == 0)
		{
			ft_printf("Process %d input is stdin\n", pos);
		}
		else
		{
			ft_printf("Process %d input is file %d\n", pos, process_fd[0]);
			dup2(process_fd[READ_END], STDIN_FILENO);
		}
		if (process_fd[WRITE_END] == STDOUT_FILENO && cmd_number > 0)
		{
			ft_printf("Process %d sending output to pipe\n", pos);
			dup2(pipe_fd[WRITE_END], STDOUT_FILENO);
		}
		else if (process_fd[WRITE_END] == STDOUT_FILENO)
		{
			ft_printf("Process %d sending output to terminal\n", pos, process_fd[1]);
			dup2(tmp_stdio_fd[WRITE_END], STDOUT_FILENO);
		}
		else 
		{
			ft_printf("Process %d sending output to file %d\n", pos, process_fd[1]);
			dup2(process_fd[WRITE_END], STDOUT_FILENO);
		}
	}
	else if (pos == cmd_number && cmd_number > 0)
	{
		close(pipe_fd[WRITE_END]);
		if (process_fd[READ_END] == 0)
		{	
			ft_printf("Process %d input is pipe\n", pos);
//			dup2(pipe_fd[READ_END], STDIN_FILENO);
		}
		else
		{
			dup2(process_fd[READ_END], STDIN_FILENO);
		}
		if (process_fd[WRITE_END] == STDOUT_FILENO)
		{
			ft_printf("Process %d sending output to stdout\n", pos);
			dup2(tmp_stdio_fd[1], STDOUT_FILENO);	
		}
		else
		{
			ft_printf("Process %d sending output to file %d\n", pos, process_fd[1]);
			dup2(process_fd[WRITE_END], STDOUT_FILENO);
		}
	}
	else
	{
		if (process_fd[WRITE_END] == STDOUT_FILENO)
		{
			dup2(pipe_fd[WRITE_END], STDOUT_FILENO);
		}
		else
		{
			dup2(process_fd[WRITE_END], STDOUT_FILENO);
		}
		if (process_fd[READ_END] == STDIN_FILENO)
		{
//			dup2(pipe_fd[READ_END], STDIN_FILENO);
		}
		else
		{
			dup2(process_fd[READ_END], STDIN_FILENO);
		}
	}
	if (execve(cmd_path, cmd, env) == -1 && errno == ENOEXEC)
		execute_script_without_shebang(cmd, env);
	//as doesn't return when execute the command well, there is no protection
	else
	{
		perror("execve");
		//free all the data if execve fails
		//230809nimai: comment free to avoid double freeing.
		free(cmd_path);
		free_list(cmd);
		free_alloc(data);		
	}
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
				ft_printf("Files opened\n");
				//redirect input
				//setup output

				// Not last
				//simple command 
				//create pipe
				if (pipe(pipe_fd) == -1)
					return (-1);
				//set singnal handlers for child process
				ft_printf("HEY");
				set_signal_handlers(0);
				ft_printf("I'm in line %d\n", __LINE__);
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
