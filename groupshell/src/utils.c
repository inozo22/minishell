/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-mada <bde-mada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 12:49:14 by bde-mada          #+#    #+#             */
/*   Updated: 2023/06/08 13:57:42 by bde-mada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*del(void **ptr)
{
	free(*ptr);
	ptr = NULL;
	return (ptr);
}

void	*del_array(void ***ptr)
{
	int	i;

	i = -1;
	while (*ptr && *ptr[++i])
		del(&(*ptr[i]));
	free(*ptr);
	*ptr = NULL;
	return (ptr);
}

void	*del_err_array(char ***ptr, int i)
{
	while (i)
		del((void **)ptr[i--]);
	free(*ptr);
	*ptr = NULL;
	return (ptr);
}
