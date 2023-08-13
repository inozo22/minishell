/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 09:32:33 by bde-mada          #+#    #+#             */
/*   Updated: 2023/08/11 15:00:21 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @note 230804nimai: at the moment, when there is no environment valur, user name will be "noname"
  */
static char	*get_user(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		if (ft_strnstr(env[i], "USER=", 5))
			break ;
	if (env[i])
		return (ft_strdup(env[i] + 5));
	else
		return (ft_strdup("noname"));
	return (NULL);
}


char	*get_prompt(t_data *data)
{
	char	*user;
	char	*prompt;
	int		prompt_len;
	int		color_len;

	user = get_user(data->env);
	prompt_len = ft_strlen(SHELL_NAME) + ft_strlen(user);
	color_len = ft_strlen(COLOR_YELLOW) + ft_strlen(COLOR_RESET) + \
	ft_strlen(COLOR_BLUE) + ft_strlen(COLOR_RESET);
	prompt = (char *)ft_calloc(prompt_len + color_len + 5, sizeof(char));
	if (!prompt)
		return (NULL);
	ft_strcpy(prompt, COLOR_YELLOW);
	ft_strcat(prompt, SHELL_NAME);
	ft_strcat(prompt, COLOR_RESET);
	ft_strcat(prompt, COLOR_BLUE);
	ft_strcat(prompt, "@");
	ft_strcat(prompt, user);
	free(user);
	ft_strcat(prompt, COLOR_RESET);
	ft_strcat(prompt, "$ ");
	return (prompt);
}

int	check_exit(char **input, t_data *data)
{
	if (input[1])
		data->return_val = ft_atoi(input[1]);
	return (INT_MAX);
}

/**
 * @note modified to control any kind of letters for pwd, echo, env
 * @note changed order of the conditions, I think will not make any error because of this. tho....
 * @note コマンドArrにして、関数をポインターで渡したらきれいに出来そうだけど、現状見やすいので放置
 * It would be neat to make it a command Arr and pass function's pointer, but it's readable, so leave it.
  */
int	check_builtin(char **input, t_data *data)
{
/* 	int i = -1;
	while (data->env[++i])
		ft_printf("env %d: %s\n", i, data->env[i]); */
	if (!input || !input[0])
		return (-1);
	ft_printf("Input0: %s\n", input[0]);
	ft_printf("Input1: %s\n", input[1]);
	if (!ft_strcmp(input[0], "cd"))
		return (built_cd(input, data));
	else if (!ft_strcmp(input[0], "export"))
		return (built_export(input, data));
	else if (!ft_strcmp(input[0], "unset"))
		return (built_unset(input, data));
	else if (!ft_strcmp(input[0], "exit"))
	{
		ft_printf("Exit found!\n");
		return (INT_MAX);
	}
	ft_strlower(input[0]);
	if (!ft_strcmp(input[0], "echo"))
		return (built_echo(input));
	else if (!ft_strcmp(input[0], "pwd"))
		return (built_pwd(data));
	else if (!ft_strcmp(input[0], "env"))
		return (built_env(input, data));
	else
		return (-1);
}

static int	process_input(char *line_read, t_data *data)
{
//	int		j;
//	char	**input;
	t_list	*cmd_list;
//	t_list	*cmd;
	int		cmd_nb;

	cmd_nb = lexer(line_read, &cmd_list);
	// while (cmd_list)
	// {
	// 	printf("cmdlist->content: %s	type: %d	cmp_pos: %d\n", cmd_list->content, cmd_list->type, cmd_list->cmd_pos);
	// 	cmd_list = cmd_list->next;
	// }
	printf("cmd_nb: %d\n", cmd_nb);//230804add
	parser(line_read);//230807add
	// while (cmd)
	// {
	// 	printf("cmd->content: %s	type: %d	cmp_pos: %d\n", cmd->content, cmd->type, cmd->cmd_pos);
	// 	cmd = cmd->next;
	// }

	t_list	*tmp;
	tmp = cmd_list;
	while (tmp)
	{
		tmp->content = expanser(tmp, data);
		printf("%sEXPANSER: Line: %d, content: %s, type: %d, pos: %d%s\n", COLOR_BLUE, __LINE__, tmp->content, tmp->type, tmp->cmd_pos, COLOR_RESET);
		tmp = tmp->next;
	}
//	exit (0);
/**
 * 
 * @note 230809 kokomade
 * @note make the expanserworking
 * 
 */


//infile, outfile obtain in expanser? ->in parser kana
	data->return_val = child_creation(NULL, NULL, cmd_list, cmd_nb, data->path, data->env, data);
	ft_lstclear(&cmd_list, free);
//	if (data->return_val == INT_MAX)
//		return (check_exit(input, data));
//	del_array((void ***) &input);
//	ft_printf("Command executed: %s with return: %d\n", input[0], data->return_val);
	return (data->return_val);
}

// struct termios termios_save;

int	minishell(t_data *data)
{
	char			*line_read;
	char			*prompt;

// these are remove ^C in the prompt
	// struct termios	termios_save;
	// struct termios	term;

	// tcgetattr(0, &termios_save);
	// tcsetattr(0, 0, &termios_save);
	// term = termios_save;
	// term.c_lflag &= ~ECHOCTL;
	// tcsetattr(0, TCSASOFT, &term);
// these are remove ^C in the prompt

	printf("pid in minishell: %d\n", data->pid);
	//set_signal_handlers(13);
	prompt = get_prompt(data);
	while (1)
	{
		set_signal_handlers(13);//230808nimai: changed from above, to recall it after child process
		line_read = readline(prompt);
		if (line_read && *line_read)
		{
/* 			if (!ft_strcmp(line_read, "^C"))
				rl_on_new_line();
			else *///230731nimai:comment
			add_history(line_read);
		}
		if (!line_read)//230731nimai: added to work ctrl+D without segfault
		{
			sig_eof(data);//check function process
			break ;
		}
		if (process_input(line_read, data) == INT_MAX)
			break ;
		free(line_read);
	}
	free(prompt);
	rl_redisplay();
	printf("\n\nBye 🗑");
	rl_clear_history();
	free(line_read);
	return (data->return_val);
}
