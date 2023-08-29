/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-mada <bde-mada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 18:22:41 by bde-mada          #+#    #+#             */
/*   Updated: 2023/08/29 15:54:08 by bde-mada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//test
//int	g_return_val;
//test

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

char	*get_shlvl(const char *envp)
{
	int		n;
	char	*num;
	char	*ret;

	n = ft_atoi(&envp[6]);
	n++;
	if (n > 999)
		n = 1;
	num = ft_itoa(n);
	ret = (char *)ft_calloc(6 + ft_strlen(num) + 1, sizeof(char));
	ft_strcpy(ret, "SHLVL=");
	ft_strcat(ret, num);
	free (num);
	return (ret);
}

pid_t	get_my_pid(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (0);
	if (pid == 0)
		exit(0);
	else
		wait(NULL);
	return (pid - 1);
}
