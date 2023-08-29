/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-mada <bde-mada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 18:22:41 by bde-mada          #+#    #+#             */
/*   Updated: 2023/08/29 15:52:54 by bde-mada         ###   ########.fr       */
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
	data->pid = pid;
	ft_printf("PID obtained: %d\n", data->pid);
	ft_printf("PID with getpid(): %d\n", getpid());
	ret = minishell(data);
	if (g_return_val)
		ret = g_return_val;
	free_alloc(data);
	return (ret);
}
