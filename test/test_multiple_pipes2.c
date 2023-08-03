/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_multiple_pipes2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-mada <bde-mada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 13:02:04 by bde-mada          #+#    #+#             */
/*   Updated: 2023/07/12 13:54:26 by bde-mada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libft/libft.h"
#include <stdio.h>
#include <fcntl.h>

# define READ_END 0
# define WRITE_END 1

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
		free(cmd_path);
	}
	ft_printf("cmd_path: %s\n", cmd_path);
	return (cmd_path);
}

void	execute(char *cmd_path, char **cmd, char **envp)
{
	if (execve(cmd_path, cmd, envp) == -1)
	{
		ft_printf("Execution failed with command: %s\n", cmd[0]);
//		error_msg("minishell", cmd[0], 1);
//		if (errno == 13 && !last)
//			errors(0, param);
//		else
//			errors(8, param);
		exit(1);
	} 
}

/* int	exit_child(int *fd_pipe, char ***cmd)
{
// 	del_array((void ***)&data->env);
//	del_array((void ***)&data->path);
	close(fd_pipe[WRITE_END]);
	error_msg("minishell: ", *cmd[0], 1);
//	errno = 2;
	del_array((void ***)cmd);
	exit(127);
} */

static void	execute_child(int *fd_pipe, char **path, char **cmd, char **env)
{
	char	*cmd_path;
	
	ft_printf("I'm in child\n");
	cmd_path = get_cmd_path(cmd[0], path);
	if (!cmd_path)
		exit (1);
//		exit_child(data, fd_pipe, &cmd);
	execute(cmd_path, cmd, env);
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

//		errors(38, param);
//	if (WIFEXITED(exit_status) && WEXITSTATUS(exit_status))
//		errors(exit_status, param);
	ft_printf("I'm in father\n");
	return (exit_status);
}

int	close_selected_pipes(int **fd_pipe, int cmd_nb)
{
	int	i;
	int	return_val;

	i = -1;
	return_val = 0;
	while (++i < cmd_nb)
	{
		if (i != cmd_nb - 1)
			if (close(fd_pipe[i][READ_END]))
				return_val = 1;
		if (i != cmd_nb)
			if (close(fd_pipe[i][WRITE_END]))
				return_val = 1;
	}
	return (return_val);
}

int	close_free_all_pipes(int **fd_pipe, int cmd_nb)
{
	int	i;
	int	return_val;

	i = -1;
	return_val = 1;
	while (++i < cmd_nb)
	{
		if (close(fd_pipe[i][READ_END]) || close(fd_pipe[i][WRITE_END]))
			return_val = 2;
		free(fd_pipe[i]);
	}
	free(fd_pipe);
	return (return_val);
}

/* int	child_creation(char ***cmd, int cmd_nb, char **path, char **envp)
{
	int		**fd_pipe;
	int		i;
	int		exit_status;
	pid_t	pid;
	
//Check to disable:
	if (!cmd)
		return (0);
//Actual function:
	i = 1;
	fd_pipe = malloc(sizeof(int *) * (cmd_nb - 1));
	if (!fd_pipe)
		return (1);
	while (--cmd_nb)
	{
		fd_pipe[cmd_nb - 1] = malloc(sizeof(int) * 2);
		if (!fd_pipe[cmd_nb - 1])
			return (1);
		if (pipe(fd_pipe[cmd_nb - 1]) == -1)
			return (1);
	}
	ft_printf("Hey\n");
	pid = fork();
	if (pid == -1)
		return (close_free_all_pipes(fd_pipe, cmd_nb));
	if (pid == 0)
		execute_child(fd_pipe, cmd[i - 1], 0, envp);
	while (++i < cmd_nb && pid != 0)
	{
		pid = fork();
		if (pid == -1)
			return (close_free_all_pipes(fd_pipe, cmd_nb));
		if (pid == 0)
			execute_child(fd_pipe, cmd[i - 1], i, envp);
	}
	waitpid(0, &exit_status, 0);
	return (0);
} */

int	check_exit_status(int e_status)
{
	if (WIFEXITED(e_status))
		return (WEXITSTATUS(e_status));
	if (WIFSIGNALED(e_status))
		return (128 + WTERMSIG(e_status));
	return (0);
}

/**
 * @param tmp_stdfd[0] = tmp_stdin
 * @param tmp_stdfd[1] = tmp_stdout
 * @param fdin[0] = fdin
 * @param fdin[1] = fdout
*/
int child_creation2(char *infile, char *outfile, char ***cmd, int cmd_number, char **path, char **env)
{
	//save in/out
	int tmp_stdin;
	int tmp_stdout;
	pid_t pid;
	int fdin;
	int fdout;
	int e_status;
	int i;

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
	while (++i < cmd_number)
	{
		//redirect input
		dup2(fdin, 0);
		close(fdin);
		//setup output
		if(i == cmd_number - 1)
		{
			// Last simple command
			if(outfile)
				fdout = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else
			{
				// Use default output 
				fdout =dup(tmp_stdout);
			}
		}
		else
		{
			// Not last
			//simple command 
			//create pipe
			int fdpipe[2];
			pipe(fdpipe);
			printf("Im here, pipe1: %d, pipe2: %d\n", fdpipe[0], fdpipe[1]);
			fdout = fdpipe[1];
			fdin = fdpipe[0];
		}
		// if/else
		// Redirect output
		dup2(fdout,1);
		close(fdout);
		// Create child process
		pid = fork();
		if (pid == 0)
		{
			//child
			printf("cmd[i][0] = %s\n", cmd[i][0]);
			execve(get_cmd_path(cmd[i][0], path), cmd[i], env);
			perror("execve");
			exit(1);
		}
	}
	//for
	//restore in/out defaults
	dup2(tmp_stdin, 0);
	dup2(tmp_stdout, 1);
	close(tmp_stdin);
	close(tmp_stdout);
	
	waitpid(pid, &e_status, 0);
	return (check_exit_status(e_status));
}

int child_creation(char ***cmd, int cmd_number, char **path, char **env) 
{
	pid_t pid;
	int e_status;
	int i;

	i = -1;
	while (++i < cmd_number)
	{
		pid = fork(); 
		if (pid == 0)
		{
			//child
			printf("cmd[%d][0] = %s\n", i, cmd[i][0]);
			execve(get_cmd_path(cmd[i][0], path), cmd[i], env);
			perror("execve");
			exit(1);
		}
		else if (pid < 0)
		{
			perror("fork");
			return (1);
		}
	}
	// Parent shell continue } // for
	// wait for last process
	waitpid(pid, &e_status, 0);
	return (check_exit_status(e_status));
}// execute

int	main(int ac, char **av, char **envp)
{
	char	***cmd;
	char 	**path;
	int		ret;
	int		i;
	int		j;
	
	i = -1;
	j = -1;
	cmd = calloc(sizeof(char **), 4);
	cmd[0] = calloc(sizeof(char *), 4);
	cmd[0][0] = ft_strdup("ls");
 	cmd[0][1] = ft_strdup("-l");
	cmd[0][2] = ft_strdup("../../Documents");
	cmd[1] = calloc(sizeof(char *), 3);
	cmd[1][0] = ft_strdup("cat");
	cmd[2] = calloc(sizeof(char *), 4);
	cmd[2][0] = ft_strdup("cat");
/* 	cmd[2][1] = ft_strdup("-l");
	cmd[2][2] = ft_strdup("../../Desktop"); */
	while(*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
		{
			path = ft_split(*(envp)+ 5, ':');
			break ;
		}
		envp++;
	}
/* 	while(path[++i])
		ft_printf("%s\n", path[i]); */
//	ret = child_creation(cmd, 3, path, envp);
	ret = child_creation2(NULL, NULL, cmd, 3, path, envp);
	ft_printf("ret = %d\n", ret);
	i = -1;
	while (cmd[++i])
	{
		j = -1;
		while (cmd[i][++j])
			free(cmd[i][j]);
		free(cmd[i]);
	}
	free(cmd);
	i = -1;
	while(path[++i])
		free(path[i]);
	free(path);
	return (0);
}
