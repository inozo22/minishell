/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 12:22:37 by nimai             #+#    #+#             */
/*   Updated: 2023/05/15 12:25:50 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
