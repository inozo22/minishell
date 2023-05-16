/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 10:19:37 by nimai             #+#    #+#             */
/*   Updated: 2023/05/15 17:10:56 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	put_shlvl_warn(int num)
{
	char	*num_str;

	num_str = ft_itoa(num);
	if (!num_str)
		minish_error_exit(1, "initialization", "malloc failed");
	write(STDERR_FILENO, "minishell: warning: shell level (", 33);
	write(STDERR_FILENO, &num_str, ft_strlen(num_str));
	write(STDERR_FILENO, ") too high, resetting to 1\n", 27);
	free (num_str);
}

static void	init_shlvl(void)
{
	t_var	*shlvl_var;
	char	*num_str;
	int		num;

	shlvl_var = get_env("SHLVL");
	if (shlvl_var && shlvl_var->value)
	{
		num = ft_atoi(shlvl_var->value);
		if (num < 0)
			num = 0;
		else
			num++;
		if (num >= 1000)
		{
			put_shlvl_warn(num);
			num = 1;
		}
	}
	else
		num = 1;
	num_str = ft_itoa(num);
	if (num_str)
		ft_setenv("SHLVL", num_str, 0);
	free (num_str);
}

static void	init_pwd(void)
{
	t_var	*pwd_var;
	char	*tmp;

	pwd_var = get_env("PWD");
	if (!pwd_var || !pwd_var->value)
	{
		tmp = getcwd(NULL, 0);
		if (tmp)
			ft_setenv("PWD", tmp, 0);
		free(tmp);
	}
	pwd_var = get_env("OLDPWD");
	if (!pwd_var)
		ft_setenv("PWD", NULL, 0);
}

void	init_g_shell(void)
{
	extern char	**env;//second gloval variable?

	sort_strarr(env);
	g_shell.cwd = NULL;
	g_shell.vars = environ2vars(env);
	g_shell.status = 0;
}

int	init_shell(void)//why it's int? can be void?
{
	init_g_shell();
	init_pwd();
	init_shlvl();
	return (0);
}

