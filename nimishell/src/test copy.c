/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 10:02:30 by nimai             #+#    #+#             */
/*   Updated: 2023/09/08 15:18:37 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "get_next_line_bonus.h"

#include <fcntl.h>
#include <stdlib.h>
//test
int	g_return_val;
//test
static int	process_input(char *line_read, t_data *data);

//TEST/////TEST////////TEST///////TEST/////////TEST////TEST////////

int	built_cd_oldpwd_test(t_data *data)
{
	char	*input[2];

	input[0] = "export";
	input[1] = "/users/nimai";

	built_export(input, data);

	input[0] = "cd";
	input[1] = "-";

	built_cd(input, data);
	return (0);
}

int	input_test(t_data *data)
{
	process_input("echo -n aaa", data);
	process_input("exit", data);
	return (0);
}

int	input_mult_test(t_data *data, char *test)
{
	int		fd;
	char	*str;

	fd = open(test, O_RDONLY);
	str = get_next_line(fd);
	while (str)
	{
		printf("%scommand line: %s%s\n", COLOR_CYAN, str, COLOR_RESET);
		process_input(str, data);
		free (str);
		str = get_next_line(fd);
	}
	return (0);
}

int	test_childcreation(t_data *data)
{
	t_list	*list;
	t_list	*tmp;
//	char	*input = "$HOME $? \'$HOME\' $?\'$HOME\'$?";
	char	*input = "echo ${HOM} ${HOME} \'${HOME}\' $HO{ME} ";
//	char	*input = "echo | cd | pwd | env";
//	char	*input = "cat < infile| cat >outfile";
//	char	*input = "cat < infile";
//	char	*input2 = "$$ $$$USER";
	char	*ret;
	int		cmd_nb;

	cmd_nb = lexer(input, &list);
	tmp = list;
	while (tmp)
	{
		ret = expanser(tmp, data);
		printf("%sEXPANSER: Line: %d, ret: %s, type: %d, pos: %d%s\n", COLOR_BLUE, __LINE__, ret, tmp->type, tmp->cmd_pos, COLOR_RESET);
		tmp = tmp->next;
	}
	child_creation(NULL, NULL, list, cmd_nb, data->path, data->env, data);
	return(0);
}

int	test_expand(t_data *data)
{
	t_list	*list;
//	char	*input = "$HOME $? \'$HOME\' $?\'$HOME\'$?";
//	char	*input = "echo $HOME$USERa $HOME $? \'$HOME\' $?\'$HOME\'$?$$";
	char	*input = "echo cd pwd env";
//	char	*input2 = "$$ $$$USER";
	char	*ret;

	lexer(input, &list);
	while (list)
	{
		ret = expanser(list, data);
		printf("%sEXPANSER: Line: %d, ret: %s, type: %d, pos: %d%s\n", COLOR_BLUE, __LINE__, ret, list->type, list->cmd_pos, COLOR_RESET);
		list = list->next;
	}
	return(0);
}

//TEST/////TEST////////TEST///////TEST/////////TEST////TEST////////

static int	process_input(char *line_read, t_data *data)
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
		tmp->content = expanser(tmp, data);
		printf("%sEXPANSER: Line: %d, content: %s, type: %d, pos: %d%s\n", COLOR_BLUE, __LINE__, tmp->content, tmp->type, tmp->cmd_pos, COLOR_RESET);
		tmp = tmp->next;
	}
	data->return_val = child_creation(NULL, NULL, cmd_list, cmd_nb, data->path, data->env, data);
	ft_lstclear(&cmd_list, free);
//	if (data->return_val == INT_MAX)
//		return (check_exit(input, data));
//	del_array((void ***) &input);
//	ft_printf("Command executed: %s with return: %d\n", input[0], data->return_val);
	return (data->return_val);
}

/**
 * @note added SHLVL increment
  */
static int	fill_env(t_data *data, char *envp[])
{
	int		i;

	i = 0;
	while (envp[i])
		i++;
	data->env = (char **)ft_calloc(i + 2, sizeof(char *));
	if (!data->env)
		return(errors(12, data));
	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "SHLVL=", 6) == 0)
		{
			data->env[i] = get_shlvl(envp[i]);
			//you can put error message when it has 1000, but I don't think anyone try to 1000 times open minishell
		}
		else if (ft_strncmp(envp[i], "OLDPWD=", 7))
			data->env[i] = ft_strdup(envp[i]);
		else
			data->env[i] = ft_strdup("OLDPWD");
		if (!data->env[i] && envp[i])
			return (errors(12, data));
	}
	ft_printf("Environment loaded\n");
	return (0);
}

static void	define_basic_env(t_data *data, char *prog_name)
{
	char	*ptr;
	char	*tmp;

	ptr = getcwd(NULL, 0);
	data->env = (char **)ft_calloc(5 + 1, sizeof(char *));
	data->env[0] = ft_strdup("PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin");
	data->env[1] = ft_strjoin("PWD=", ptr);
	data->env[2] = ft_strdup("OLDPWD");
	data->env[3] = ft_strdup("SHLVL=1");
	tmp = ft_strjoin("_=", ptr);
	free(ptr);
	ptr = tmp;
	tmp = ft_strjoin(tmp, "/");
	data->env[4] = ft_strjoin(tmp, prog_name);
	free(ptr);
	free(tmp);
	ft_printf("No environment available, baseline created\n");
}

static t_data	*init_data(char *envp[], char *prog_name)
{
	t_data	*data;

	data = NULL;
	data = (t_data *)ft_calloc(1, sizeof(t_data));
	if (!data)
		errors(12, data);
	data->return_val = 0;
	if (!*envp)
		define_basic_env(data, prog_name);
	else
		if (fill_env(data, envp))
			return (NULL);
	set_path_list(data);
	return (data);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data	*data;
	pid_t	pid;
	int		ret;

	g_return_val = 0;
	pid = get_my_pid();
	if (!pid)
		return (1);
	if ((argc == 3 && ft_strcmp(argv[1], "-c")) || argc != 1)
		exit (error_file(argv[0], argv[1]));
	data = init_data(envp, argv[0]);
	if (!data)
		return (1);
	printf("env[0] %s\n", data->env[0]);
	data->pid = pid;

	//if you want to put any test function, here

//	test_expand(data);
//	test_childcreation(data);
//test_checkquotes();
//	input_mult_test(data, "u_echo.test");
//	input_test(data);
	built_cd_oldpwd_test(data);



	////////////////////////////////////////


	if (argv[1])
		ret = minishell(data);
	if (g_return_val)
		ret = g_return_val;
	free_alloc(data);
	return (ret);
}
