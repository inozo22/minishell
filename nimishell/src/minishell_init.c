/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-mada <bde-mada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 18:22:41 by bde-mada          #+#    #+#             */
/*   Updated: 2023/10/20 17:02:10 by bde-mada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @note 230804nimai: at the moment, when there is no environment valur,
 * user name will be "unknown"
  */
char	*get_prompt(t_data *data)
{
	char	*user;
	char	*prompt;
	int	i;

	i = -1;
	while (data->env[++i])
		if (ft_strnstr(data->env[i], "USER=", 5))
			break ;
	if (data->env[i])
		user = ft_strdup(data->env[i] + 5);
	else
		user = ft_strdup("unknown");
	if (!user)
		errors(ENOMEM, data);
	prompt = ft_strjoin_many(7, COLOR_YELLOW, SHELL_NAME, COLOR_BLUE, \
							"@", user, COLOR_RESET, "$ ");
	if (!prompt)
		errors(ENOMEM, data);
	free(user);
	return (prompt);
}

/* void	set_path_list(t_data *data)
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
} */

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
		if (!ft_isdigit((int)envp[i]))
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
