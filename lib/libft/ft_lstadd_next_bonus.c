/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_next_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-mada <bde-mada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 17:49:49 by bde-mada          #+#    #+#             */
/*   Updated: 2023/07/03 14:40:32 by bde-mada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_next(t_list **lst, t_list *newnode)
{
	if (*lst)
	{
		newnode->next = (*lst)->next;
		(*lst)->next = newnode;
	}
	else
		*lst = newnode;
}
