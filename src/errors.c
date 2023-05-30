/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 17:20:27 by nimai             #+#    #+#             */
/*   Updated: 2023/05/30 14:07:25 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief get absolute path to move
 * @author nimai
 * @return destination path as string
 */
void	heap_error(int flag)
{
	if (flag == 1)
	{
		ft_printf("memory allocate failure\n");

	}
}

