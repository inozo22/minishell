/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 12:18:50 by bde-mada          #+#    #+#             */
/*   Updated: 2023/09/14 15:30:01 by nimai            ###   ########.fr       */
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
	if (g_return_val)
		return (g_return_val);
	if (WIFEXITED(e_status))
		return (WEXITSTATUS(e_status));
	if (WIFSIGNALED(e_status))
		return (128 + WTERMSIG(e_status));
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
	ft_bzero(fd, 2 * sizeof(int));
	while (lst && lst->cmd_pos == pos)
	{
		if (lst->type == REDIR_IN)
			fd[0] = open(lst->content, O_RDONLY);
		if (lst->type == REDIR_OUT)
			fd[1] = open(lst->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (lst->type == APPEND)
			fd[1] = open(lst->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd[0] == -1 || fd[1] == -1)
			return (1);
		lst = lst->next;
	}
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

int	child_execution(char **cmd, char **env, char **path, t_data *data)
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

int	executer(char *outfile, t_list *lst, int cmd_number, \
				char **path, char **env, t_data *data)
{
	int		tmp_stdin;
	int		tmp_stdout;
	pid_t	pid;
	int		fd[2];
	int		e_status;
	int		pos;
	char	**cmd;

	printf(COLOR_RED"%d/%s	g_return_val: %d%s\n", __LINE__, __FILE__, g_return_val, COLOR_RESET);

	e_status = 0;
	tmp_stdin = dup(STDIN_FILENO);
	tmp_stdout = dup(STDOUT_FILENO);
	pos = 0;
	//set the initial input
/* 	if (infile)
		fdin = open(infile, O_RDONLY);
	else
	{
		// Use default input
		fdin = dup(tmp_stdin);
	} */
	// IMPORTANTE: check if the last command is exit
/* 	if (ft_strcmp(cmd[cmd_number - 1][0], "exit"))
		return (0); */
	while (lst)
//	while (++i < cmd_number)
	{
		cmd = NULL;
		ft_printf("Current cmd pos: %d, cmd_number: %d\n", lst->cmd_pos, cmd_number);
		if (lst->cmd_pos == pos)
		{
			get_iofiles_fd(fd, lst, pos);
			get_heredoc_input(lst, pos, data->env, data->pid);
			//redirect input
			if (pos != 0)
			{
 				dup2(fd[0], STDIN_FILENO);
				close(fd[0]);		
			}
			//setup output
			if (pos == cmd_number)
			{
				// Last simple command
				if (outfile)
					fd[1] = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				else
				{
					// Use default output 
					fd[1] = dup(tmp_stdout);
				}
			}
			else
			{
				// Not last
				//simple command 
				//create pipe
				int	fdpipe[2];
				pipe(fdpipe);
				fd[1] = fdpipe[1];
				fd[0] = fdpipe[0];
			}
			// if/else
			// Redirect output
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
			//set singnal handlers for child process
			set_signal_handlers(0);
			ft_printf("I'm in line %d\n", __LINE__);
			cmd = fill_current_cmd(lst, pos, data->env, data->pid);
			if (!cmd)
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
			int is_builtin = check_builtin(cmd, data);
			ft_printf("\nCheck builtin return: %d\n", is_builtin);
			if (is_builtin >= 0)
				return (free(cmd), is_builtin);
			
			// Create child process
			pid = fork();
			if (pid == 0)
				child_execution(cmd, env, path, data);
			while (lst && lst->cmd_pos == pos)
				lst = lst->next;
			pos++;
			free(cmd);
		}
	}
	//for
	//restore in/out defaults
	dup2(tmp_stdin, 0);
	dup2(tmp_stdout, 1);
	close(tmp_stdin);
	close(tmp_stdout);

	waitpid(0, &e_status, WUNTRACED);
//	waitpid(pid, &e_status, WUNTRACED);
	return (check_exit_status(e_status));
}
