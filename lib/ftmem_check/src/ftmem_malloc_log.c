/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftmem_check copy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 10:17:23 by nimai             #+#    #+#             */
/*   Updated: 2023/05/10 12:17:24 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftmem_check.h"
#include <stdio.h>

void	*ftmem_malloc_log(size_t size, const char *file, unsigned int line, t_mem *mem)
{
	void	*ptr;

	ptr = NULL;
	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	mem->log[mem->i].ptr = ptr;
	mem->log[mem->i].file = file;
	mem->log[mem->i].size = size;
	mem->log[mem->i].line = line;
	mem->i++;
	return (ptr);
}
