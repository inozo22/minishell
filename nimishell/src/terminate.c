/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-mada <bde-mada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:24:59 by bde-mada          #+#    #+#             */
/*   Updated: 2023/09/05 15:11:20 by bde-mada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	*free_list(char **list)
{
	int	i;

	i = -1;
	while (list[++i])
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
	free_list(data->path);
	data->env = NULL;
	data->path = NULL;
}
