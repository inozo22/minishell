/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 10:17:23 by nimai             #+#    #+#             */
/*   Updated: 2023/05/11 15:19:30 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem_check.h"

t_mem	*mem_init(t_mem *mem)
{
	int	i;

	mem = malloc(sizeof(t_mem));
	if (!mem)
		return (NULL);
	i = -1;
	while (++i < MAX_MEM)
	{
		mem->log[i].ptr = NULL;
		mem->log[i].file = NULL;
		mem->log[i].size = 0;
		mem->log[i].line = 0;
	}
	mem->i = 0;
	return (mem);
}
