/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:44:25 by nimai             #+#    #+#             */
/*   Updated: 2023/05/30 17:24:45 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	**ptr_free(void **ptr)
{
	int	i;

	if (!ptr)
		return (NULL);
	i = 0;
	while (i < av_amount((char **)ptr))
	{
		//free(ptr[i]);
		ptr[i] = NULL;
		i++;
	}
	//free (ptr);
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
