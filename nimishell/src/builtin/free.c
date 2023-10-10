/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:44:25 by nimai             #+#    #+#             */
/*   Updated: 2023/10/10 11:59:33 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_free(void *ptr)
{
	free (ptr);
	ptr = NULL;
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
