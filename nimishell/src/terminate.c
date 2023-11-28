/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:24:59 by bde-mada          #+#    #+#             */
/*   Updated: 2023/11/28 16:06:19 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*free_list(char **list)
{
	int	i;

	i = -1;
	while (list && list[++i])
	{
		free(list[i]);
		list[i] = NULL;
	}
	free(list);
	return (NULL);
}

void	free_alloc(t_data *data)
{
	free_list(data->env);
	data->env = NULL;
}
