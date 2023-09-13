/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-mada <bde-mada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 18:22:41 by bde-mada          #+#    #+#             */
/*   Updated: 2023/09/05 15:40:16 by bde-mada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//global variable for return value
int	g_return_val;

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
	ft_printf("Environment loaded\n");
	return (0);
}

static int	define_basic_env(t_data *data, char *prog_name)
{
	char	*ptr;
	char	*tmp_prog_name;

	ptr = getcwd(NULL, 0);
	data->env = (char **)ft_calloc(5 + 1, sizeof(char *));
	if (!data->env)
		return(errors(12, data));
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
	set_path_list(data);
	data->exit_status = 0;
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;

	g_return_val = 0;
	data.pid = get_my_pid();
	if (!data.pid)
		return (1);
	if (init_data(&data, envp, argv[0]))
		return (1);
/* 	ft_printf("PID obtained: %d\n", data.pid);
	ft_printf("argc: %d\n", argc);
	ft_printf("PID with getpid(): %d\n", getpid()); */
	if (argc != 1)
	{
		if ((argc == 3 && !ft_strcmp(argv[1], "-c")))
			return (process_input(argv[2], &data));
		else
			exit (error_file(argv[0], argv[1]));
	}
	minishell(&data);
	free_alloc(&data);
	return (g_return_val);
}
