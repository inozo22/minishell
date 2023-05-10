/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 11:26:23 by nimai             #+#    #+#             */
/*   Updated: 2023/05/01 11:07:53 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*pmem;

	pmem = malloc(count * size);
	if (pmem == NULL)
		return (NULL);
	ft_memset(pmem, '\0', (count * size));
	return (pmem);
}
