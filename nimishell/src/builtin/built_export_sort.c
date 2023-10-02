/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export_sort.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:17:55 by nimai             #+#    #+#             */
/*   Updated: 2023/10/02 14:07:09 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	swap_pairs(t_export_box *first, t_export_box *second)
{
	char	*tmp_val;
	char	*tmp_name;
	int		tmp_equal;

	tmp_val = first->val;
	tmp_name = first->name;
	tmp_equal = first->equal;
	first->val = second->val;
	first->name = second->name;
	first->equal = second -> equal;
	second->val = tmp_val;
	second->name = tmp_name;
	second -> equal = tmp_equal;
}

/**
 * @brief manage "builtin" export cmd.
 * @author nimai
 * @param **av "export", "ABC=abc".
 */
int	get_pivot(t_export_box box[], int left, int right)
{
	int	pivot;
	int	i;
	int	j;

	i = left;
	j = right + 1;
	pivot = left;
	while (i < j)
	{
		while (i < j && box[++i].name && box[pivot].name && \
		ft_strcmp(box[i].name, box[pivot].name) < 0)
			;
		while (j && box[pivot].name && box[--j].name && \
		ft_strcmp(box[pivot].name, box[j].name) < 0)
			;
		if (i < j)
			swap_pairs(&box[i], &box[j]);
	}
	swap_pairs(&box[pivot], &box[j]);
	return (j);
}

void	quick_sort(t_export_box box[], int left, int right)
{
	int	pivot;

	if (left < right)
	{
		pivot = get_pivot(box, left, right);
		quick_sort(box, left, pivot - 1);
		quick_sort(box, pivot + 1, right);
	}
}
