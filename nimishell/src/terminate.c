/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-mada <bde-mada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:24:59 by bde-mada          #+#    #+#             */
/*   Updated: 2023/09/01 15:07:58 by bde-mada         ###   ########.fr       */
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
	data->env = NULL;
}

int	errors(int error_id, t_data *data)
{
	perror("minishell:");
	if (error_id == ENOMEM)
		ft_printf("Cannot allocate memory\n");
	free_alloc(data);
	return (error_id);
}
