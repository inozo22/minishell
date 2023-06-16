/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 18:22:41 by bde-mada          #+#    #+#             */
/*   Updated: 2023/06/16 11:10:35 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief main structure initialization 
 * @note 230614nimai: maybe better put "OLDPWD" without value here (at the moment put in export)
 * with cmd env will not be shown until doesn't have value, but with cmd export yes.
 */
static t_data	*init_data(char *envp[])
{
	t_data	*data;
	int		len[2];

	data = NULL;
	ft_bzero(len, 2 * sizeof(int));
	data = (t_data *)ft_calloc(1, sizeof(t_data));
	if (!data)
		errors(12, data);
	while (envp[len[0]])
		len[0]++;
	data->env = (char **)ft_calloc(len[0] + 1, sizeof(char *));
	if (!data->env)
		errors(12, data);
	len[0] = 0;
	while (envp[len[0]])
	{
		if (ft_strncmp(envp[len[0]], "OLDPWD=", 7))
			data->env[len[1]++] = ft_strdup(envp[len[0]++]);
		else
			len[0]++;
		if (!data->env[len[1] - 1] && envp[len[0] - 1])
			errors(12, data);
	}
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
