/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-mada <bde-mada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:24:59 by bde-mada          #+#    #+#             */
/*   Updated: 2023/05/31 14:23:50 by bde-mada         ###   ########.fr       */
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
	list = NULL;
	return (list);
}

void	*free_alloc(t_data *data)
{
	free_list(data->env);
	exit(EXIT_SUCCESS);
}

void	errors(int error_id, t_data *data)
{
	perror("minishell:");
	if (error_id == 12)
		ft_printf("Mem error\n");
	free_alloc(data);
}
