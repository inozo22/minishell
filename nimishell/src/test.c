/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 10:02:30 by nimai             #+#    #+#             */
/*   Updated: 2023/09/23 10:05:50 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "get_next_line_bonus.h"

#include <fcntl.h>
#include <stdlib.h>
//test
volatile int	g_return_val;
//test

//TEST/////TEST////////TEST///////TEST/////////TEST////TEST////////

int	built_export_test(t_data *data)
{
	char	**input_ex;
	char	**input_export;

	input_export = ft_calloc(1, sizeof(char *));
	input_export[0] = "export";
	input_ex = ft_calloc(4, sizeof(char *));
	input_ex[0] = "export";
	input_ex[1] = "a";
	input_ex[2] = "b";
	input_ex[3] = "c=aaa";

	built_export(input_ex, data);
	printf(COLOR_GREEN"=== I did export! ===%s\n", COLOR_RESET);
	printf(COLOR_BLUE"=== check check ===%s\n", COLOR_RESET);
	built_export(input_export, data);
	printf(COLOR_BLUE"=== check check ===%s\n\n", COLOR_RESET);

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
//	char	*input = "$HOME $? \'$HOME\' $?\'$HOME\'$?";
//	char	*input = "\"$$\"555\"$HOME\"'$USER'$PWD"; expexted: "222555/Users/nimai$USER/Users/nimai/42/42cursus/minishell/nimishell"
//	char	*input2 = "$$ $$$USER";
	char	*ret;
	// char	*input = "\"$HOME\"'$USER'";

	// char *input1 = "$HOME$USER$PWD$$";
	// printf("%stest1	EXPANSER: Line: %d, ret: %s%s\n", COLOR_GREEN, __LINE__, input1, COLOR_RESET);
	// ret = expander(input1, data->env, 111);
	// printf("%stest1	ret		: %s%s\n", COLOR_BLUE, ret, COLOR_RESET);
	// printf("%stest1	expected	: %s%s\n\n", COLOR_GREEN, "/Users/nimainimai/Users/nimai/42/42cursus/minishell/nimishell111", COLOR_RESET);




	char *input10 = "$000";
	// char *input1 = "\"$\"";
	printf("%stest10	EXPANSER: Line: %d, ret: %s%s\n", COLOR_GREEN, __LINE__, input10, COLOR_RESET);
	ret = expander(input10, data->env, 111);
	printf("%stest10	ret		: %s%s\n", COLOR_BLUE, ret, COLOR_RESET);
	printf("%stest10	expected	: %s%s\n\n", COLOR_GREEN, "nimishell00", COLOR_RESET);

	// char *input1 = "\"$ $ $ $ $ $\"";
	// // char *input1 = "\"$\"";
	// printf("%stest1	EXPANSER: Line: %d, ret: %s%s\n", COLOR_GREEN, __LINE__, input1, COLOR_RESET);
	// ret = expander(input1, data->env, 111);
	// printf("%stest1	ret		: %s%s\n", COLOR_BLUE, ret, COLOR_RESET);
	// printf("%stest1	expected	: %s%s\n\n", COLOR_GREEN, "$ $ $ $ $ $", COLOR_RESET);




	// char *input2 = "$HOME$?\'$HOME\'$?\'$HOME\'$?";
	// printf("%stest2	EXPANSER: Line: %d, ret: %s%s\n", COLOR_GREEN, __LINE__, input2, COLOR_RESET);
	// ret = expander(input2, data->env, 222);
	// printf("%stest2	ret		: %s%s\n", COLOR_BLUE, ret, COLOR_RESET);
	// printf("%stest2	expected	: %s%s\n\n", COLOR_GREEN, "/Users/nimai0$HOME0$HOME0", COLOR_RESET);

	// char *input3 = "\"$PWD\"aaa$USER'$HOME''\"'";
	// printf("%stest3	EXPANSER: Line: %d, ret: %s%s\n", COLOR_GREEN, __LINE__, input3, COLOR_RESET);
	// ret = expander(input3, data->env, 333);
	// printf("%stest3	ret		: %s%s\n", COLOR_BLUE, ret, COLOR_RESET);
	// printf("%stest3	expected	: %s%s\n\n", COLOR_GREEN, "/Users/nimai/42/42cursus/minishell/nimishellaaanimai$HOME\"", COLOR_RESET);



	// char *input4 = "123\"$USER\"456\"$HOME\"\"$USER\"\"aaa\"";
	// printf("%stest3	EXPANSER: Line: %d, ret: %s%s\n", COLOR_GREEN, __LINE__, input4, COLOR_RESET);

	// ret = expander(input4, data->env, 666);
	// printf("%stest3	ret		: %s%s\n", COLOR_BLUE, ret, COLOR_RESET);
	// printf("%stest3	expected	: %s%s\n\n", COLOR_GREEN, "123nimai456/Users/nimainimaiaaa", COLOR_RESET);

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

	test_expand(data);
//	test_childcreation(data);
//test_checkquotes();
//	input_mult_test(data, "u_echo.test");
//	input_test(data);
//	built_cd_oldpwd_test(data);
//	built_unset_test(data);
//	built_cd_oldpwd_unset_test(data);
//	built_export_test(data);

	////////////////////////////////////////


	if (argv[1])
		ret = minishell(data);
	if (g_return_val)
		ret = g_return_val;
	free_alloc(data);
	free(data);
	return (ret);
}
