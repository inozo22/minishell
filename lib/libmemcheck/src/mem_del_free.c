/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_del_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 10:17:23 by nimai             #+#    #+#             */
/*   Updated: 2023/05/11 15:19:24 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem_check.h"

void	mem_del_free(void *ptr, t_mem *mem)
{
	int	i;

	i = -1;
	while (++i < MAX_MEM)
	{
		if (mem->log[i].ptr == ptr)
		{
			mem->log[i].ptr = NULL;
			mem->log[i].file = NULL;
			mem->log[i].size = 0;
			mem->log[i].line = 0;
			break ;
		}
	}
	free (ptr);
}
