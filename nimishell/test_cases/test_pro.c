/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pro.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 10:02:30 by nimai             #+#    #+#             */
/*   Updated: 2023/11/25 17:42:27 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "get_next_line_bonus.h"

#include <fcntl.h>
#include <stdlib.h>
#include <termios.h>
//test
volatile int	g_return_val;
//test

//TEST/////TEST////////TEST///////TEST/////////TEST////TEST////////

int	built_export_test(t_data *data)
{
	// char	**input_ex;

//to change things with export	
	// input_ex = ft_calloc(4, sizeof(char *));
	// input_ex[0] = "export";
	// input_ex[1] = "a";
	// input_ex[2] = "b";
	// input_ex[3] = "c=aaa";
	// printf(COLOR_GREEN"=== I enter test export! ===%s\n", COLOR_RESET);

	// built_export(input_ex, data);
	// printf(COLOR_GREEN"=== I did export! ===%s\n", COLOR_RESET);
//to change things with export

//to output export
	char	**input_export = NULL;
	input_export = ft_calloc(2, sizeof(char *));
	input_export[0] = "export";
	input_export[1] = NULL;
	printf(COLOR_BLUE"=== check check ===%s\n", COLOR_RESET);
	built_export(input_export, data);
	printf(COLOR_BLUE"=== check check ===%s\n\n", COLOR_RESET);

	free (input_export);
//	sleep (1);

	// char	**input1;

	// input1 = ft_calloc(2, 1);
	// input1[0] = "unset";
	// input1[1] = "PWD";

	// built_unset(input1, data);
	// printf(COLOR_GREEN"=== I did unset! ===%s\n", COLOR_RESET);

	// printf(COLOR_BLUE"=== check check ===%s\n", COLOR_RESET);
	// built_export(input_export, data);
	// printf(COLOR_BLUE"=== check check ===%s\n\n", COLOR_RESET);

	// char	*input_cd[2];
	// input_cd[0] = "cd";
	// input_cd[1] = "/users/nimai/42/42cursus";

	// built_cd(input_cd, data);
	// printf(COLOR_GREEN"=== I did cd! ===%s\n", COLOR_RESET);
	// printf(COLOR_BLUE"=== check check ===%s\n", COLOR_RESET);
	// built_export(input_export, data);
	// printf(COLOR_BLUE"=== check check ===%s\n\n", COLOR_RESET);
	return (0);
}

int	built_cd_oldpwd_unset_test(t_data *data)
{
	char	**input_ex;
	char	**input_export;

	input_export = ft_calloc(1, 1);
	input_export[0] = "export";
	input_ex = ft_calloc(2, 1);
	input_ex[0] = "export";
	input_ex[1] = "OLDPWD=/users/nimai";

	built_export(input_ex, data);
	printf(COLOR_GREEN"=== I did export! ===%s\n", COLOR_RESET);
	printf(COLOR_BLUE"=== check check ===%s\n", COLOR_RESET);
	built_export(input_export, data);
	printf(COLOR_BLUE"=== check check ===%s\n\n", COLOR_RESET);

//	sleep (1);

	char	**input1;

	input1 = ft_calloc(2, 1);
	input1[0] = "unset";
	input1[1] = "PWD";

	built_unset(input1, data);
	printf(COLOR_GREEN"=== I did unset! ===%s\n", COLOR_RESET);

	printf(COLOR_BLUE"=== check check ===%s\n", COLOR_RESET);
	built_export(input_export, data);
	printf(COLOR_BLUE"=== check check ===%s\n\n", COLOR_RESET);

	char	*input_cd[2];
	input_cd[0] = "cd";
	input_cd[1] = "/users/nimai/42/42cursus";

	built_cd(input_cd, data);
	printf(COLOR_GREEN"=== I did cd! ===%s\n", COLOR_RESET);
	printf(COLOR_BLUE"=== check check ===%s\n", COLOR_RESET);
	built_export(input_export, data);
	printf(COLOR_BLUE"=== check check ===%s\n\n", COLOR_RESET);
	return (0);
}


int	built_unset_test(t_data *data)
{
	char	**input1;

	input1 = ft_calloc(2, 1);
	input1[0] = "unset";
	input1[1] = "HOME";
	built_unset(input1, data);
	printf("I did unset!\n");

	sleep (1);

	char	**input2;

	input2 = ft_calloc(1, 1);
	input2[0] = "export";
	built_export(input2, data);
	printf("I did export!\n");

	return (0);
}

int	built_cd_oldpwd_test(t_data *data)
{
	char	**input_ex;
	char	*input_cd[2];

	input_ex = ft_calloc(2, 1);
	input_ex[0] = "export";
	input_ex[1] = "OLDPWD=/users/nimai";

	built_export(input_ex, data);

	input_cd[0] = "cd";
	input_cd[1] = "-";

	built_cd(input_cd, data);
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

// int	test_childcreation(t_data *data)
// {
// 	t_list	*list;
// 	t_list	*tmp;
// //	char	*input = "$HOME $? \'$HOME\' $?\'$HOME\'$?";
// 	char	*input = "echo ${HOM} ${HOME} \'${HOME}\' $HO{ME} ";
// //	char	*input = "echo | cd | pwd | env";
// //	char	*input = "cat < infile| cat >outfile";
// //	char	*input = "cat < infile";
// //	char	*input2 = "$$ $$$USER";
// 	char	*ret;
// 	int		cmd_nb;

// 	cmd_nb = lexer(input, &list);
// 	tmp = list;
// 	while (tmp)
// 	{
// 		ret = expanser(tmp, data);
// 		printf("%sEXPANSER: Line: %d, ret: %s, type: %d, pos: %d%s\n", COLOR_BLUE, __LINE__, ret, tmp->type, tmp->cmd_pos, COLOR_RESET);
// 		tmp = tmp->next;
// 	}
// 	child_creation(NULL, NULL, list, cmd_nb, data->path, data->env, data);
// 	return(0);
// }

int	test_expand(t_data *data)
{
	// (void)data;
	// char	*input = "$HOME $? \'$HOME\' $?\'$HOME\'$?";
//	char	*input = "\"$$\"555\"$HOME\"'$USER'$PWD"; expexted: "222555/Users/nimai$USER/Users/nimai/42/42cursus/minishell/nimishell"
	// char	*input2 = "$$ $$$USER";
	char	*ret;
	int		i[3];

	i[2] = 0;
	// char	*input = "\"$HOME\"'$USER'";

	// char *input1 = "$HOME$USER$PWD$$";
	// printf("%stest1	EXPANSER: Line: %d, ret: %s%s\n", COLOR_GREEN, __LINE__, input1, COLOR_RESET);
	// ret = expander(input1, data, &i[2]);
	// printf("%stest1	ret		: %s%s\n", COLOR_BLUE, ret, COLOR_RESET);
	// // printf("%stest1	expected	: %s%s\n\n", COLOR_GREEN, "/Users/nimainimai/Users/nimai/42/42cursus/minishell/nimishell111", COLOR_RESET);




	// char *input10 = "ls";
	// char *input1 = "\"$\"";
	// printf("%stest10	EXPANSER: Line: %d, ret: %s%s\n", COLOR_GREEN, __LINE__, input10, COLOR_RESET);
	// ret = expander(input10, data->env, 111);
	// printf("%stest10	ret		: %s%s\n", COLOR_BLUE, ret, COLOR_RESET);
	// printf("%stest10	expected	: %s%s\n\n", COLOR_GREEN, "ls", COLOR_RESET);
	// free (ret);
	// char *input1 = "\"$ $ $ $ $ $\"";
	// // char *input1 = "\"$\"";
	// printf("%stest1	EXPANSER: Line: %d, ret: %s%s\n", COLOR_GREEN, __LINE__, input1, COLOR_RESET);
	// ret = expander(input1, data, &i[2]);
	// printf("%stest1	ret		: %s%s\n", COLOR_BLUE, ret, COLOR_RESET);
	// printf("%stest1	expected	: %s%s\n\n", COLOR_GREEN, "$ $ $ $ $ $", COLOR_RESET);

	// free (ret);


	// char *input2 = "$HOME$?\'$HOME\'$?\'$HOME\'$?";
	// printf("%stest2	EXPANSER: Line: %d, ret: %s%s\n", COLOR_GREEN, __LINE__, input2, COLOR_RESET);
	// ret = expander(input2, data->env, 222);
	// printf("%stest2	ret		: %s%s\n", COLOR_BLUE, ret, COLOR_RESET);
	// printf("%stest2	expected	: %s%s\n\n", COLOR_GREEN, "/Users/nimai0$HOME0$HOME0", COLOR_RESET);
	// free (ret);
	// char *input3 = "\"$PWD\"aaa$USER'$HOME''\"'";
	// printf("%stest3	EXPANSER: Line: %d, ret: %s%s\n", COLOR_GREEN, __LINE__, input3, COLOR_RESET);
	// ret = expander(input3, data->env, 333);
	// printf("%stest3	ret		: %s%s\n", COLOR_BLUE, ret, COLOR_RESET);
	// printf("%stest3	expected	: %s%s\n\n", COLOR_GREEN, "/Users/nimai/42/42cursus/minishell/nimishellaaanimai$HOME\"", COLOR_RESET);

	// free (ret);

	char *input4 = "123\"$USER\"456\"$HOME\"\"$USER\"\"aaa\"";
	printf("%stest3	EXPANSER: Line: %d, ret: %s%s\n", COLOR_GREEN, __LINE__, input4, COLOR_RESET);

	ret = expander(input4, data, &i[2]);
	printf("%stest3	ret		: %s%s\n", COLOR_BLUE, ret, COLOR_RESET);
	printf("%stest3	expected	: %s%s\n\n", COLOR_GREEN, "123nimai456/Users/nimainimaiaaa", COLOR_RESET);

	// char *input5 = "\"$PWD\"$.USER'$HOME'";
	// printf("%stest4	EXPANSER: Line: %d, ret: %s%s\n", COLOR_GREEN, __LINE__, input5, COLOR_RESET);
	// ret = expander(input5, data->env, 555);
	// printf("%stest4	ret		: %s%s\n", COLOR_BLUE, ret, COLOR_RESET);
	// printf("%stest4	expected	: %s%s\n\n", COLOR_GREEN, "/Users/nimai/42/42cursus/minishell/nimishell$.USER$HOME", COLOR_RESET);

	// char *input6 = "555$USER'aaa'\"'\"'\"'\"\"''$$";
	// printf("%stest5	EXPANSER: Line: %d, ret: %s%s\n", COLOR_GREEN, __LINE__, input6, COLOR_RESET);

	// ret = expander(input6, data->env, 666);
	// printf("%stest5	ret		: %s%s\n", COLOR_BLUE, ret, COLOR_RESET);
	// printf("%stest5	expected	: %s%s\n\n", COLOR_GREEN, "555nimaiaaa'\"666", COLOR_RESET);
	free (ret);
	return(0);
}

//TEST/////TEST////////TEST///////TEST/////////TEST////TEST////////

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
		return (errors(12, data));
	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "SHLVL=", 6) == 0)
		{
			data->env[i] = get_shlvl(envp[i]);
			if (!data->env[i])
				return (errors(ENOMEM, data));
		}
		else if (ft_strncmp(envp[i], "OLDPWD=", 7))
			data->env[i] = ft_strdup(envp[i]);
		else
			data->env[i] = ft_strdup("OLDPWD");
		if (!data->env[i] && envp[i])
			return (errors(ENOMEM, data));
	}
	return (0);
}

static int	define_basic_env(t_data *data, char *prog_name)
{
	char	*ptr;
	char	*tmp_prog_name;

	ptr = getcwd(NULL, 0);
	data->env = (char **)ft_calloc(5 + 1, sizeof(char *));
	if (!data->env)
		return (errors(12, data));
	data->env[0] = ft_strdup(DEFAULT_PATH);
	data->env[1] = ft_strjoin("PWD=", ptr);
	data->env[2] = ft_strdup("OLDPWD");
	data->env[3] = ft_strdup("SHLVL=1");
	tmp_prog_name = ft_substr(prog_name, 2, ft_strlen(prog_name) - 2);
	data->env[4] = ft_strjoin_many(4, "_=", ptr, "/", tmp_prog_name);
	free(tmp_prog_name);
	free(ptr);
	ft_printf("No environment available, baseline created\n");
	return (0);
}

static int	init_data(t_data *data, char *envp[], char *prog_name)
{
	if (!*envp && define_basic_env(data, prog_name))
		return (1);
	else if (*envp && fill_env(data, envp))
		return (1);
	ft_printf("Environment loaded\n");
	set_path_list(data);
	data->exit_status = 0;
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data			data;
	struct termios	termios_save;

	g_return_val = 0;
	data.pid = get_my_pid();
	if (!data.pid)
		return (1);
	if (init_data(&data, envp, argv[0]))
		return (1);
	if (argc != 1)
	{
		if ((argc == 3 && !ft_strcmp(argv[1], "-c")))
			return (process_input(argv[2], &data));
		else
			exit (error_file(argv[1]));
	}
	// these remove ^C in the prompt
	// CORREGIR MENSAJE DE ERROR

	if (set_terminal_attributes(&termios_save) == 1)
		return (1);



// 	//if you want to put any test function, here

	test_expand(&data);
// //	test_childcreation(data);
// //test_checkquotes();
// //	input_mult_test(data, "u_echo.test");
// //	input_test(data);
// //	built_cd_oldpwd_test(data);
// //	built_unset_test(data);
// //	built_cd_oldpwd_unset_test(data);
 	// built_export_test(&data);

// 	////////////////////////////////////////

		//return (errors(12, data));
//	minishell(&data);
	free_alloc(&data);
	tcsetattr(0, 0, &termios_save);
	return (g_return_val);


	
// 	t_data	*data;
// 	pid_t	pid;
// 	int		ret;

// 	g_return_val = 0;
// 	pid = get_my_pid();
// 	if (!pid)
// 		return (1);
// 	if ((argc == 3 && ft_strcmp(argv[1], "-c")) || argc != 1)
// 		return (process_input(argv[2], &data));
// 	data = init_data(envp, argv[0]);
// 	if (!data)
// 		return (1);
// 	printf("env[0] %s\n", data->env[0]);
// 	data->pid = pid;



// 	if (argv[1])
// 		ret = minishell(data);
// 	if (g_return_val)
// 		ret = g_return_val;
// 	free_alloc(data);
// 	free(data);
// 	return (ret);
}
