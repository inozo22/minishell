/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-mada <bde-mada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 09:32:33 by bde-mada          #+#    #+#             */
/*   Updated: 2023/12/11 15:50:40 by bde-mada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/history.h>

/* 	//DELETE
	t_list *test = cmd_list;
	ft_printf(COLOR_CYAN"Printing list"COLOR_RESET"\n");
	while (test)
	{
		ft_printf("Content: %s type: %d pos: %d\n", test->content, \
					test->type, test->cmd_pos);
		test = test->next;
	} 
	ft_printf("\n");*/

/**
 */
int	process_input(char *line_read, t_data *data)
{
	t_list	*cmd_list;
	int		ret;

	cmd_list = NULL;
	data->max_pid = 0;
	data->cmd_nb = lexer(line_read, &cmd_list, data);
	if (data->cmd_nb == -1)
		return (1);
	if (set_fds(data, 0) == 1)
		return (ft_lstclear(&cmd_list, free), 0);
	ret = check_single_builtin(cmd_list, data);
	if ((data->cmd_nb == 0 && ret == 0) || ret == 127 || ret == -1)
		return (ft_lstclear(&cmd_list, free), 0);
	executer(cmd_list, data);
	ft_lstclear(&cmd_list, free);
	get_exit_status(data, 1);
	return (0);
}

/**
 * @note 231117nimai: this function is to check if the
 * 						command line is totally white.
 * @return if the entire line is white, free the string(line_read) and return 1.
  */
int	ft_entire_isspace(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!ft_isspace(str[i]))
			return (0);
	free (str);
	return (1);
}

int	minishell(t_data *data)
{
	char	*line_read;
	char	*prompt;

	prompt = get_prompt(data);
	while (1)
	{
		set_signal_handlers(1);
		line_read = readline(prompt);
		if (line_read == NULL)
			break ;
		if (line_read && *line_read)
		{
			add_history(line_read);
			if (ft_entire_isspace(line_read))
				continue ;
			process_input(line_read, data);
		}
		else
			get_exit_status(data, 0);
		line_read = my_free(line_read);
		if (data->exit_status)
			break ;
	}
	ft_printf("\nBye! (T-T)/\n");
	return (rl_clear_history(), free(prompt), obtain_pwd_home(NULL, 99), 0);
}
