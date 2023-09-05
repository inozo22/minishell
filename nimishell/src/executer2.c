/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-mada <bde-mada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 12:18:50 by bde-mada          #+#    #+#             */
/*   Updated: 2023/09/05 16:05:15 by bde-mada         ###   ########.fr       */
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
	ft_printf("cmd_path: %s\n", cmd_path);
	return (cmd_path);
}

/**
 * @note 230811nimai: add g_return_val, check if there is another way to reset g_return_val
 */
int	check_exit_status(int e_status)
{
/* 	int	ret;

	ret = 0;
	if (g_return_val)
	{
		ret = g_return_val;
		g_return_val = 0;
		return (ret);
	} */
	if (WIFEXITED(e_status))
		return (WEXITSTATUS(e_status));
	if (WIFSIGNALED(e_status))
		return (128 + WTERMSIG(e_status));
	return (0);
}

int execute_script_without_shebang(char **cmd, char **env)
{
	char *new_argv[2];
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
//int child_creation(char *infile, char *outfile, char ***cmd, int cmd_number, char **path, char **env, t_data *data)
int executer(char *infile, char *outfile, t_list *lst, int cmd_number, char **path, char **env, t_data *data)
{
	//save in/out
	int tmp_stdin;
	int tmp_stdout;
	pid_t pid;
	int fdin;
	int fdout;
	int e_status;
	int i;

//	e_status = 0;
	tmp_stdin = dup(0);
	tmp_stdout = dup(1);
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
/* 	if (ft_strcmp(cmd[cmd_number - 1][0], "exit"))
		return (0); */
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
