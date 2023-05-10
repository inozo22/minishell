/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftmem_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 10:17:23 by nimai             #+#    #+#             */
/*   Updated: 2023/05/10 12:18:41 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftmem_check.h"
#include <stdio.h>

void	ftmem_check(t_mem *mem)
{
	int	i;

	i = -1;
	while (++i <= mem->i)
	{
		if (mem->log[i].ptr != NULL)
		{
			printf("=Memory leaks=\n");
			printf("adress: %p\n", mem->log[i].ptr);
			printf("size: %u\n", (unsigned int)mem->log[i].size);
			printf("Leak point: %s:%u\n\n", mem->log[i].file, mem->log[i].line);
		}
	}
}
