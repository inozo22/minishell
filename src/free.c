/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:44:25 by nimai             #+#    #+#             */
/*   Updated: 2023/05/26 16:31:07 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	**ptr_free(void **ptr)
{
	int	i;

	if (!ptr)
		return (NULL);
	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		ptr[i] = NULL;
		i++;
	}
	free (ptr);
	return (NULL);
}

/* void	all_free(t_box *stack_a, t_box *stack_b, t_bunch *ps)
{
	if (ps->len)
		strs_clear(ps->strs, ps->len);
	list_clear(ps->answer);
	free(ps);
	list_clear(stack_a);
	list_clear(stack_b);
} */
