/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export_sort.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:17:55 by nimai             #+#    #+#             */
/*   Updated: 2023/05/26 15:34:30 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	swap_pairs(t_export_box *first, t_export_box *second)
{
	char	*tmp_val;
	char	*tmp_name;


	tmp_val = first->val;
	tmp_name = first->name;
	first->val = second->val;
	first->name = second->name;
	second->val = tmp_val;
	second->name = tmp_name;
}

int	get_pivot_value(t_export_box box[], int left, int right)
{
	int	pivot;
	int	i;
	int	j;

	i = left;
	j = right + 1;
	pivot = left;
	while (i < j)
	{
		while (i < j && ft_strncmp(box[++i].name, box[pivot].name, 2000) < 0)
			;
		while (j && ft_strncmp(box[pivot].name, box[--j].name, 2000) < 0)
			;
		if (i < j)
		{
			swap_pairs(&box[i], &box[j]);
		}
	}
	swap_pairs(&box[pivot], &box[j]);
	return (j);
}

void	quick_sort(t_export_box box[], int left, int right)
{
	int	pivot;

	if (left < right)
	{
		pivot = get_pivot_value(box, left, right);
		quick_sort(box, left, pivot - 1);
		quick_sort(box, pivot + 1, right);
	}
}

/**
 * qsort doesn't work, but should work...
 * retry tomorrow
 * 
 * 
 */