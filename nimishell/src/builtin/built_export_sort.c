/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export_sort.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:17:55 by nimai             #+#    #+#             */
/*   Updated: 2023/10/08 09:43:29 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void	sort_list(t_list *list)
{
	int		len;
	t_list	*head;
	char	*tmp;

	head = list;
	while (list->next)
	{
		len = ft_strchr(list->content, '=') - list->content;
		if (len < ft_strchr(list->next->content, '=') - list->next->content)
			len = ft_strchr(list->next->content, '=') - list->next->content;
		if (ft_strncmp(list->content, list->next->content, len) > 0)
		{
			tmp = list->content;
			list->content = list->next->content;
			list->next->content = tmp;
			list = head;
			continue ;
		}
		list = list->next;
	}
	int i = 0;
	list = head;
	while (list)
	{
		printf("list[%d]: %s\n", i, list->content);
		list = list->next;
		i++;
	}
}
