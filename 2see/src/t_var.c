/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_var.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 12:26:56 by nimai             #+#    #+#             */
/*   Updated: 2023/05/15 12:45:46 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_var	*allloc_new_var(const char *key, const char *value, bool is_shell_var)
{
	t_var	*new_var;

	new_var = ft_calloc(1, sizeof(t_var));
	if (!new_var)
		return (NULL);
	new_var->key = ft_strdup(key);
	if (value)
		new_var->value = ft_strdup(value);
	new_var->is_shell_var = is_shell_var;
	return (new_var);
}

static t_var	*add_var(t_var **vars, t_var *new_var)
{
	t_var	*cur;
	t_var	*prev;

	prev = NULL;
	cur = *vars;
	while (cur && ft_strcmp(new_var->key, cur->key) > 0)
	{
		prev = cur;
		cur = cur->next;
	}
	new_var->next = cur;
	if (!prev)
		*vars = new_var;
	else if (!cur)
		prev->next = new_var;
	else
		prev->next = new_var;
	return (new_var);
}

t_var	*add_new_var(t_var **vars, const char *key, const char *value, bool is_shell_var)
{
	t_var	*new_var;

	new_var = allloc_new_var(key, value, is_shell_var);
	if (!new_var)
		return (NULL);
	if (!*vars)
		*vars = new_var;
	else
		add_var(vars, new_var);
	return (new_var);
}
