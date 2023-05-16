/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_setter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 12:18:21 by nimai             #+#    #+#             */
/*   Updated: 2023/05/15 12:22:18 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_setenv(const char *key, const char *value, bool is_shell_var)
{
	t_var	*var;

	var = get_env(key);
	if (var)
	{
		if (value)
		{
			free((void *)var->value);
			var->value = ft_strdup(value);
		}
		var->is_shell_var = is_shell_var;
	}
	else if (!add_new_var(&g_shell.vars, key, value, is_shell_var))
		return (-1);
	return (0);
}
