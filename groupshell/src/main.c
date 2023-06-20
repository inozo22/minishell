/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 18:22:41 by bde-mada          #+#    #+#             */
/*   Updated: 2023/06/20 10:40:17 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_env(char *envp[], t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "OLDPWD=", 7))
			data->env[j++] = ft_strdup(envp[i++]);
		else
			i++;
		if (!data->env[j - 1] && envp[i - 1])
			errors(12, data);
	}
	data->env[j] = ft_strdup("OLDPWD");
}

/**
 * @note 230620nimai: didnt't work when there is no OLDPWD, so I put checker and change the allocation size according to the length.
 */
static t_data	*init_data(char *envp[])
{
	t_data	*data;
	int		len;
	int		flag;

	data = NULL;
	len = -1;
	flag = 1;
	data = (t_data *)ft_calloc(1, sizeof(t_data));
	if (!data)
		errors(12, data);
	while (envp[++len])
	{
		if (ft_strncmp(envp[len], "OLDPWD", 6) == 0)
			flag = 0;
	}
	data->env = (char **)ft_calloc(len + (flag + 1), sizeof(char *));
	if (!data->env)
		errors(12, data);
	fill_env(envp, data);
	data->return_val = 0;
	return (data);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data	*data;

	if (argc != 1 || argv[1])
		return (error_file(argv[0], argv[1]));
	data = init_data(envp);
	if (!data)
		return (1);
	minishell(data);
	free_alloc(data);
	return (0);
}
