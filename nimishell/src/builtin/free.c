/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:44:25 by nimai             #+#    #+#             */
/*   Updated: 2023/09/26 15:11:40 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_free(void *ptr)
{
	free (ptr);
	ptr = NULL;
}

void	*arr_free(t_export *list)
{
	int	i;

	i = 0;
	while (list->box[i].name)
	{
		if (list->box[i].name)
		{
			free (list->box[i].name);
			list->box[i].name = NULL;
		}
		if (list->box[i].val)
		{
			free (list->box[i].val);
			list->box[i].val = NULL;
		}
		i++;
	}
	return (NULL);
}

char	**strs_free(char **strs)
{
	int	i;
	int	len;

	i = 0;
	len = av_amount(strs);
	while (i < len - 1)
	{
		free (strs[i]);
		strs[i] = NULL;
		i++;
	}
	free (strs);
	return (NULL);
}
