/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_var2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:14:50 by nimai             #+#    #+#             */
/*   Updated: 2023/05/15 12:06:33 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_var	kvstr2var(char	*kvstr, bool is_shell_var)
{
	char	**kvarr;
	t_var	*new_var;

	kvarr = split_first_c(kvstr, '=');
	if (!kvarr)
		return (NULL);
	if (!kvarr[0] || !ft_strlen(kvarr[0]))//the same conditions?
	{
		free_ptrarr((void **)kvarr);
		return (NULL);
	}
	new_var = ft_calloc(sizeof(t_var, 1));
	new_var->key = kvarr[0];
	new_var->value = kvarr[1];
	new_var->is_shell_var = is_shell_var;
	free (kvarr);
	return (new_var);
}

t_var	*environ2vars(char **env)
{
	int		i;
	t_var	*first;
	t_var	*last;
	t_var	*tmp;

	i = 0;
	first = NULL;
	last = NULL;
	while (env[i])
	{
		tmp = kvstr2var(env[i], false);
		if (!tmp)
			minish_error_exit(1, "environ2t_var", "failed add var");
		if (last)
			last->next = tmp;
		last = tmp;
		if (!first)
			first = last;
		i++;
	}
	return (first);
}
