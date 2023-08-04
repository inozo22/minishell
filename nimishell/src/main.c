/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 18:22:41 by bde-mada          #+#    #+#             */
/*   Updated: 2023/08/04 09:42:58 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_path_list(t_data *data)
{
	int	i;

	i = -1;
	while (data->env[++i])
	{
		if (!ft_strncmp(data->env[i], "PATH=", 5))
		{
			data->path = ft_split(data->env[i] + 5, ':');
			if (!data->path)
				errors(12, data);
			break ;
		}
	}
}

static int	fill_env(t_data *data, char *envp[])
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	data->env = (char **)ft_calloc(i + 2, sizeof(char *));
	if (!data->env)
		return(errors(12, data));
	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "OLDPWD=", 7))
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

pid_t	get_my_pid(void)
{
	pid_t	pid;

	pid = fork();
	printf("pid in get_my_pid: %d\n", pid);
	if (pid == -1)
		return (0);
	if (pid == 0)
		exit(0);
	else
		wait(NULL);
	return (pid - 1);
	/**
	 * 
	 * @note nannde 1 hii teru, arbitrary number?
	  */
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data	*data;
	pid_t	pid;
	int		ret;

	pid = get_my_pid();
	if (!pid)
		return (1);
	if ((argc == 3 && ft_strcmp(argv[1], "-c")) || argc != 1)
		exit (error_file(argv[0], argv[1]));
	data = init_data(envp, argv[0]);
	if (!data)
		return (1);
	data->pid = pid;
	printf("pid: %d\n", data->pid);
	// int i = -1;
	// while (data->env[++i])
	// 	printf("Env %d with ptr: %p: %s\n", i, (void *)data->env[i], data->env[i]);
	ret = minishell(data);
	free_alloc(data);
	return (ret);
}
