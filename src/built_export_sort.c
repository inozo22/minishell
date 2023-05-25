/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export_sort.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:17:55 by nimai             #+#    #+#             */
/*   Updated: 2023/05/25 18:09:22 by nimai            ###   ########.fr       */
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
		while (i < j && ft_strncmp(box[i + 1].name, box[pivot].name, ft_strlen(box[pivot].name)) < 0)
			i++;
		//while (j && (int)box[pivot].name[c] < (int)box[--j].name[c])
		while (j && ft_strncmp(box[pivot].name, box[j - 1].name, ft_strlen(box[j - 1].name)) < 0)
			j--;
		if (i < j)
		{
			swap_pairs(&box[i], &box[j]);
		}
	}
/* 	while (i < j)
	{
		while (i < j && (int)box[++i].name[c] < (int)box[pivot].name[c])
			;
		while (j && (int)box[pivot].name[c] < (int)box[--j].name[c])
			;
		if (i < j)
		{
			swap_pairs(&box[i], &box[j]);
		}
	} */
	swap_pairs(&box[pivot], &box[j]);
	return (j);
}

void	quick_sort(t_export_box box[], int left, int right, int flag)
{
	int	pivot = 0;

	if (left < right)
	{
		if (flag == SORT_VALUE)
		{
			pivot = get_pivot_value(box, left, right);
		}
		else
			;
/* 		if (flag == SORT_ID)
		{
			pivot = get_pivot_id(box, left, right);
		} */
		quick_sort(box, left, pivot - 1, flag);
		quick_sort(box, pivot + 1, right, flag);
	}
}

/**
 * qsort doesn't work, but should work...
 * retry tomorrow
 * 
 * 
 */