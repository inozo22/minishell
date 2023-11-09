/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-mada <bde-mada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 12:18:50 by bde-mada          #+#    #+#             */
/*   Updated: 2023/11/09 11:35:06 by bde-mada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>//it's not necessary in POSIX.1

/**
 * @author bde-mada
 */
/* char	**fill_current_cmd(t_list *lst, int pos, char **envp, pid_t pid)
{
	char	**cmd;
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = lst;
	while (tmp && tmp->cmd_pos == pos)
	{
		if (tmp->type == WORD || tmp->type == PIPE)
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
		if (lst->type == WORD || lst->type == PIPE)
			cmd[++i] = expander(lst->content, envp, pid);
		lst = lst->next;
	}
	return (cmd);
} */

int	count_command(t_list *lst, int pos)
{
	int	ret;

	ret = 0;
	while (lst && lst->cmd_pos == pos)
	{
		if (lst->type == WORD || lst->type == PIPE || lst->type == QUOTE)
			ret++;
		lst = lst->next;
	}
	return (ret);
}

void	obtain_cmd_again(char ***cmd, char *str, int flag)
{
	free_list(*cmd);
	if (flag == 2)
	{
		*cmd = (char **)ft_calloc(2, sizeof(char *));
		(*cmd)[0] = ft_strdup(str);
		(*cmd)[1] = NULL;
	}
	else
		*cmd = ft_split(str, 32);
}

char	**fill_current_cmd(t_list *lst, int pos, t_data *data)
{
	char		**cmd;
	char		*tmp;
	char		*keep = NULL;
	int			i;
	int			flag;
	int			type_flag;
	char *temp = NULL;

	flag = 0;
	type_flag = 0;
	i = count_command(lst, pos);
	if (!i)
		return (NULL);
	cmd = (char **)ft_calloc(i + 1, sizeof(char *));
	if (!cmd)
		return (NULL);
	i = -1;
	while (lst && lst->cmd_pos == pos)
	{
		if (lst->type == WORD || lst->type == PIPE || lst->type == QUOTE)
		{
			tmp = expander(lst->content, data, &flag);
			if (*tmp)
				cmd[++i] = ft_strdup(tmp);
			free (tmp);
		}
		if (lst->type == 39 && lst->content[ft_strlen(lst->content) - 1] == 34)
			type_flag = 2;
		else if (lst->type == 39 || lst->content[ft_strlen(lst->content) - 1] == 34)
			type_flag = 0;
		else
			type_flag = 1;
		lst = lst->next;
		temp = keep;
		if (cmd[i])
			keep = ft_strjoin_many(3,temp, " ", cmd[i]);
		free (temp);
	}
	ft_printf("Line: %d keep: %s flag: %d type_flag: %d\n", __LINE__, keep, flag, type_flag);
	if (flag && type_flag)
		obtain_cmd_again(&cmd, keep, type_flag);
	return (free (keep), cmd);
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

/* int	get_heredoc_input(t_list *lst, int pos, char **envp, pid_t pid)
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
} */

int	get_heredoc_input(t_list *lst, int pos, t_data *data)
{
	char	*tmp_eof;

	tmp_eof = NULL;
	while (lst && lst->cmd_pos == pos)
	{
		if (lst->type == HERE_DOC)
			tmp_eof = lst->content;
		lst = lst->next;
	}
	if (tmp_eof && heredoc_read(tmp_eof, data))
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
	ft_printf("cmd_path: %s\n", cmd_path);
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

int	executer(t_list *lst, int cmd_number, char **env, t_data *data)
{
	int		tmp_stdio_fd[2];
	pid_t	pid;
	int		process_fd[2];
	int		e_status;
	int		pos;
	char	**cmd;
	int		pipe_fd[2];
	int		max_pid;
	char	**path;

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
	path = set_path_list(data);
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
				&& get_heredoc_input(lst, pos, data) == 0)
			{
				ft_printf("FDs set\n");
				if (pipe(pipe_fd) == -1)
					return (-1);
				//set singnal handlers for child process
				ft_printf("HEY\n");
				set_signal_handlers(0);
				cmd = fill_current_cmd(lst, pos, data);
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
				{
					// ///////0925nimai add to remove memory leaks from expander
					// j = -1;
					// while (cmd[++j])
					// {
					// 	free (cmd[j]);
					// 	cmd[j] = NULL;
					// }
					// ///////0925nimai add to remove memory leaks from expander
					return (free_list(cmd), is_builtin);
				}

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
		free_list(cmd);
		// strs_free(cmd);
		///////0925nimai add to remove memory leaks from expander
		// int j = -1;
		// while (cmd[++j])
		// {
		// 	free (cmd[j]);
		// 	cmd[j] = NULL;
		// }
		///////0925nimai add to remove memory leaks from expander
	//	free(cmd);
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
	return (0);
}
