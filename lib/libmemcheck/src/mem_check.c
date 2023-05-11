/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 10:17:23 by nimai             #+#    #+#             */
/*   Updated: 2023/05/11 15:26:08 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem_check.h"

void	mem_check(t_mem *mem)
{
	int	i;

	i = -1;
	while (++i <= mem->i)
	{
		if (mem->log[i].ptr != NULL)
		{
			printf("=Memory leaks=\n");
			printf("adress\t\t:%p\n", mem->log[i].ptr);
			printf("size\t\t:%u\n", (unsigned int)mem->log[i].size);
			printf("Leak point\t:%s:%u\n\n", mem->log[i].file, mem->log[i].line);
		}
	}
}
