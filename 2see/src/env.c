/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 12:22:37 by nimai             #+#    #+#             */
/*   Updated: 2023/05/22 17:11:08 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_val(const char *env_key)
{
	t_var	*var;

	if (!ft_strcmp(env_key, "?"))
		return (ft_itoa(get_status()));
	var = get_env(env_key);
	if (!var || !var->value)
		return (NULL);
	return (ft_strdup(var->value));
}

t_var	*get_env(const char *env_key)
{
	t_var	*cur;

	cur = g_shell.vars;
	while (cur)
	{
		if (!ft_strcmp(env_key, cur->key))
			return (cur);
		cur = cur->next;
	}
	return (NULL);
}
