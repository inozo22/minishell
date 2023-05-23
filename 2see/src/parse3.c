/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:01:07 by nimai             #+#    #+#             */
/*   Updated: 2023/05/17 17:29:35 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parse_hdoc_list	*parse_concat_heredocs(t_parse_ast *head, t_parse_ast *tail)
{
	t_parse_hdoc_list	*list;

	if (!head || !head->heredocs)
	{
		if (tail)
			return (tail->heredocs);
		else
			return (NULL);
	}
	list = head->heredocs;
	while (list->next)
		list = list->next;
	if (tail)
		list->next = tail->heredocs;
	return (head->heredocs);
}

t_parse_hdoc_list	*parse_new_heredocs(t_parse_node_redirection *redirection)
{
	t_parse_hdoc_list	*ret;

	ret = malloc(sizeof(t_parse_hdoc_list));
	if (!ret)
		parse_fatal_error();
	ret->redirection = redirection;
	ret->next = NULL;
	return (ret);
}

