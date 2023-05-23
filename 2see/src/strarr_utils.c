/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strarr_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 10:55:17 by nimai             #+#    #+#             */
/*   Updated: 2023/05/15 11:12:13 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	swap_strarr(char **strs, int i, int j)
{
	char	*tmp;

	tmp = strs[i];
	strs[i] = strs[j];
	strs[j] = tmp;
}

static int	partition_strarr(char **strs, int p, int r)
{
	int	i;
	int	j;

	i = p - 1;
	j = p;
	while (j < r)
	{
		if (ft_strcmp(strs[j], strs[r]) < 0)
		{
			i++;
			swap_strarr(strs, i, j);
		}
		j++;
	}
	swap_strarr(strs, i + 1, r);
	return (i + 1);
}

static void	quick_sort_strarr(char **strs, int p, int r)
{
	int	q;

	if (p < r)
	{
		q = partition_strarr(strs, p, r);
		quick_sort_strarr(strs, p, q - 1);
		quick_sort_strarr(strs, q + 1, p);
	}
}

void	sort_strarr(char **strs)
{
	if (!strs || !ptrarr_len(void **)strs)
		return ;
	quick_sort_strarr(strs, 0, ptrarr_len((void **)strs) - 1);
}
