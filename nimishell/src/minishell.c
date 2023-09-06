/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-mada <bde-mada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 09:32:33 by bde-mada          #+#    #+#             */
/*   Updated: 2023/09/05 16:04:32 by bde-mada         ###   ########.fr       */
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

int	check_exit(char **input)
{
	if (input[1])
		g_return_val = ft_atoi(input[1]);
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
//	update_last_executed_cmd(data, input[0]);
	if (!input[0])
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
		return (built_exit(input, data, 1));
	if (!ft_strcmp(input[0], "echo"))
		return (built_echo(input));
	else if (!ft_strcmp(input[0], "pwd"))
		return (built_pwd(data));
	else if (!ft_strcmp(input[0], "env"))
		return (built_env(input, data));
	else
		return (-1);
}

int	process_input(char *line_read, t_data *data)
{
//	int		j;
//	char	**input;
	t_list	*cmd_list;
//	t_list	*cmd;
	int		cmd_nb;
	t_list	*tmp;

	cmd_nb = lexer(line_read, &cmd_list);
	parser(line_read);//230807add
	tmp = cmd_list;
	while (tmp)
	{
		tmp->content = expander(tmp, data);
		printf("%sEXPANDER: Line: %d, content: %s, type: %d, pos: %d%s\n", COLOR_BLUE, __LINE__, tmp->content, tmp->type, tmp->cmd_pos, COLOR_RESET);
		tmp = tmp->next;
	}
	tmp = cmd_list;
	if (cmd_nb == 0)
	{
		while (tmp)
		{
			//SET THE EXIT INPUT FROM NULL TO DOUBLE ARRAY
			if (tmp->type == WORD && !ft_strcmp(tmp->content, "exit") && built_exit(NULL, data, 0) == 0)
			{
				ft_lstclear(&cmd_list, free);
				return (0);
			}
			tmp = tmp->next;
		}
	}
//	exit (0);
/**
 * 
 * @note 230809 kokomade
 * @note make the expanserworking
 * 
 */


//infile, outfile obtain in expanser? ->in parser kana
	g_return_val = executer(NULL, cmd_list, cmd_nb, data->path, data->env, data);
	ft_printf("Return val: %d\n", g_return_val);
	ft_lstclear(&cmd_list, free);
//	if (data->return_val == INT_MAX)
//		return (check_exit(input, data));
//	del_array((void ***) &input)in	;
//	ft_printf("Command executed: %s with return: %d\n", input[0], data->return_val);
	return (g_return_val);
}

// struct termios termios_save;

/**
 * @brief set terminal attributes to remove ^C in the prompt
  */
static int	set_terminal_attributes(struct termios *termios_save)
{
	struct termios	term;

	if (tcgetattr(0, termios_save))
		return (1);
	term = *termios_save;
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSASOFT, &term);
	return (0);
}

static int	clean_exit(char *prompt, char *line_read, struct termios *term_save)
{
	free(prompt);
	printf("\nBye 🗑\n");
//	rl_clear_history();
	free(line_read);
	tcsetattr(0, 0, term_save);
	return (0);
}

int	minishell(t_data *data)
{
	char			*line_read;
	char			*prompt;

// these are remove ^C in the prompt
	struct termios	termios_save;

// CORREGIR MENSAJE DE ERROR
	if (set_terminal_attributes(&termios_save) == 1)
		return (1);
		//return (errors(12, data));
	//set_signal_handlers(13);
	prompt = get_prompt(data);
	while (1)
	{
		set_signal_handlers(13);//230808nimai: changed from above, to recall it after child process
		line_read = readline(prompt);
		if (line_read && *line_read)
/* 			if (!ft_strcmp(line_read, "^C"))
				rl_on_new_line();
			else *///230731nimai:comment
			add_history(line_read);
		if (!line_read)//230731nimai: added to work ctrl+D without segfault
		{
			g_return_val = 0;
			break ;
		}
		process_input(line_read, data);
		if (data->exit_status)
			break ;
		free(line_read);
	}
	rl_clear_history();
	return (clean_exit(prompt, line_read, &termios_save));
}
