/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 18:22:41 by bde-mada          #+#    #+#             */
/*   Updated: 2023/09/14 12:19:54 by nimai            ###   ########.fr       */
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
				errors(ENOMEM, data);
			break ;
		}
	}
}

/**
 * @note add checker to protect not numeric value
 * @note case controled:
 * 1. when there is non numeric letter, change to 1
 * 2. if it will be 1000, change to null
 * 3. if it will be more than 1000, gain message and change to 1
 * MSG=> bash: warning: shell level (1011) too high, resetting to 1
 * 4. if it's out of the int(2147483647), change to 0
 * 5. otherwise add 1
 */
char	*get_shlvl(const char *envp)
{
	int		n;
	char	*num;
	char	*ret;
	int		i;

	i = 6;
	while (envp[i])
	{
		if (ft_isdigit((int)&envp[i]))
			return (ft_strdup("SHLVL=1"));
		i++;
	}
	n = ft_atoi(&envp[6]);
	n++;
	if (n < 0)
		return (ft_strdup("SHLVL=0"));
	if (n == 1000)
		return (ft_strdup("SHLVL="));
	if (n > 1000)
		return (warning_message(1, n), ft_strdup("SHLVL=1"));
	num = ft_itoa(n);
	ret = (char *)ft_calloc(6 + ft_strlen(num) + 1, sizeof(char));
	if (!ret)
		return (NULL);
	return (ft_strcpy(ret, "SHLVL="), ft_strcat(ret, num), free (num), ret);
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
