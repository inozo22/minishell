/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-mada <bde-mada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 12:18:50 by bde-mada          #+#    #+#             */
/*   Updated: 2023/12/06 13:34:44 by bde-mada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>//it's not necessary in POSIX.1

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

void	init_cmd(char ***cmd, char *str, int *i)
{
	if (i[1] == 5)
		*cmd = ft_split(str, ' ');
	else
	{
		*cmd = (char **)ft_calloc(2, sizeof(char *));
		(*cmd)[0] = ft_strdup(str);
		(*cmd)[1] = NULL;
	}
	i[0] = av_amount(*cmd);
}

/**
 * @param i[1]: flag
 * @param i[2]: type_flag
 * @param i[3]: old type_flag
  */
void	obtain_cmd(char ***cmd, char *str, int *i)
{
	char	**new;
	int		j;

	if (!str || !*str)
		return ;
	new = NULL;
	j = -1;
	if (!*cmd)
		init_cmd(cmd, str, i);
	else if (*cmd && **cmd)
	{
		new = (char **)ft_calloc(i[0] + 2, sizeof(char *));
		if (!new)
			return ;
		new[i[0] + 1] = NULL;
		new[i[0]] = ft_strdup(str);
		while (++j < i[0])
			new[j] = ft_strdup((*cmd)[j]);
		free_list(*cmd);
		*cmd = new;
	}
	i[0] = av_amount(*cmd);
}

/**
 * i[0]: i
 * i[1]: flag
 * i[2]: type_flag//not use
 * i[3]: old type_flag//not use
 * i[2]: variable count
  */
char	**fill_current_cmd(t_list *lst, int pos, t_data *data)
{
	char		**cmd;
	char		*expanded;
	int			i[3];

	ft_bzero(i, 3 * sizeof(int));
	i[0] = count_command(lst, pos);
	if (!i[0])
		return (NULL);
	cmd = NULL;
	i[0] = 0;
	while (lst && lst->cmd_pos == pos)
	{
		if (lst->type == WORD || lst->type == PIPE || lst->type == QUOTE)
			expanded = expander(lst->content, data, i);
		else
		{
			lst = lst->next;
			continue ;
		}
		obtain_cmd(&cmd, expanded, i);
		free (expanded);
		lst = lst->next;
	}
	//DELETE
	if (cmd)
	{
		ft_printf(COLOR_CYAN"Printing cmd"COLOR_RESET"\n");
		int j = -1;
		while (cmd[++j])
			ft_printf("cmd[%d] = %s\n", j, cmd[j]);
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

int	get_heredoc_input(t_list *lst, int pos, t_data *data)
{
	char	*tmp_eof;

	tmp_eof = NULL;
	//DELETE
	ft_printf("get_heredoc_input\n");
	while (lst && lst->cmd_pos == pos)
	{
		//DELETE
		ft_printf("lst->type: %d, lst->content: %s\n", lst->type, lst->content);
		if (lst->type == HERE_DOC)
		{
			tmp_eof = lst->content;
			ft_printf("tmp_eof: %s\n", tmp_eof);
		}
		lst = lst->next;
	}
	if (tmp_eof && heredoc_read(tmp_eof, data))
		return (1);
	return (0);
}

int	child_execution(char **cmd, char **path, t_data *data, int pos)
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
	redir_setup(pos, data->cmd_nb, data);
	ft_printf("cmd_path: %s\n\n", cmd_path);
	if (execve(cmd_path, cmd, data->env) == -1 && errno == ENOEXEC)
//		execute_script_without_shebang(cmd, data->env);
	//as doesn't return when execute the command well, there is no protection
	ft_printf(SH_NAME": %s: %s", cmd[0], strerror(errno));
	//free all the data if execve fails
	free_list(cmd);
	free_alloc(data);		
	exit(EXIT_FAILURE);
}

int child(char **cmd, t_data *data, int pos)
{
	int		is_builtin;
	char	**path;

	is_builtin = check_builtin(cmd, data);
	if (is_builtin >= 0)		
		return(free_list(cmd), is_builtin);
//	ft_printf("fd: %d %d %d\n", fd[0], fd[2], fd[4]);
	path = set_path_list(data);
	child_execution(cmd, path, data, pos);
	exit(EXIT_FAILURE);
}

void father(char **cmd, t_data *data, int pos)
{
	free_list(cmd);
	close(data->pipe_fd[WRITE_END]);
	dup2(data->pipe_fd[READ_END], STDIN_FILENO);
	if (data->process_fd[READ_END] != STDIN_FILENO)
		close(data->process_fd[READ_END]);
	if (data->process_fd[WRITE_END] != STDOUT_FILENO)
		close(data->process_fd[WRITE_END]);
	if (pos == data->cmd_nb)
	{	
		dup2(data->tmp_stdio_fd[0], STDIN_FILENO);
		dup2(data->tmp_stdio_fd[1], STDOUT_FILENO);
	}
}

static int fork_setup(char **cmd, t_data *data, int pos)
{
	if (pipe(data->pipe_fd) == -1)
		return (-1);
	data->return_val = 0;
	data->max_pid = fork();
	if (data->max_pid == -1)
		return (-1);
	if (data->max_pid == 0)
	{
		//child
		child(cmd, data, pos);
	}
	else
	{
		//father
		father(cmd, data, pos);
		if (pos == data->cmd_nb)
		{	
			dup2(data->tmp_stdio_fd[0], STDIN_FILENO);
			dup2(data->tmp_stdio_fd[1], STDOUT_FILENO);
		}
	}
	return (0);
}

int executer(t_list *cmd_list, t_data *data)
{
	char	**cmd;
	int		pos;

	//DELETE
	ft_printf(COLOR_CYAN"EXECUTER START\n"COLOR_RESET);
	ft_printf("cmd_number: %d\n\n", data->cmd_nb);
	data->tmp_stdio_fd[0] = dup(STDIN_FILENO);
	data->tmp_stdio_fd[1] = dup(STDOUT_FILENO);
	while (cmd_list)
	{
		pos = cmd_list->cmd_pos;
		if (get_iofiles_fd(data->process_fd, cmd_list, pos) \
			|| get_heredoc_input(cmd_list, pos, data))
			return (-1);
		set_signal_handlers(0);
		//DELETE
		ft_printf("\nFDs set in pos: %d\n", pos);
		ft_printf("process_fd[0] = %d\n", data->process_fd[0]);
		ft_printf("process_fd[1] = %d\n", data->process_fd[1]);
		ft_printf("\n");
		cmd = fill_current_cmd(cmd_list, pos, data);
		//231127nimai: to add variable "_"
		// update_last_executed_cmd(data, cmd);
		if (!cmd || !(*cmd))
		{	
			//Error setup
			return (-1);
		}
		if (fork_setup(cmd, data, pos) == -1)
			return (-1);
		while (cmd_list && cmd_list->cmd_pos == pos)
			cmd_list = cmd_list->next;
	}
	return (0);
}
