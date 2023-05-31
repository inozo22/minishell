/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:44:25 by nimai             #+#    #+#             */
/*   Updated: 2023/05/31 15:32:46 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*arr_free(t_export *list)
{
	int	i;

	i = 0;
	while (list->box[i].name)
	{
		if (list->box[i].name)
			free (list->box[i].name);
		list->box[i].name = NULL;
		if (list->box[i].val)
			free (list->box[i].val);
		list->box[i].val = NULL;
		//list->box[i] = NULL;
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
	while (i < len)
	{
		free (strs[i]);
		strs[i] = NULL;
		i++;
	}
	free (strs);
	return (NULL);
}

void	**ptr_free(void **ptr)
{
	int	i;

	if (!ptr)
		return (NULL);
	i = 0;
	while (i < av_amount((char **)ptr))
	{
		free(ptr[i]);
		ptr[i] = NULL;
		i++;
	}
	free (ptr);
	return (NULL);
}

void	*all_tmp_free(t_temp *temp)
{
	if (temp->argv)
		ptr_free((void **)temp->argv);
	if (temp->envp)
		ptr_free((void **)temp->envp);
	free (temp);
	return (NULL);
}
