/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:23:09 by nimai             #+#    #+#             */
/*   Updated: 2023/05/17 16:40:43 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_parse_ast_list	**get_ast_list(void)
{
	static t_parse_ast_list	*list;

	return (&list);
}

static t_parse_ast_list	*create_ast(void)
{
	t_parse_ast_list	*list;

	list = malloc(sizeof(t_parse_ast_list));
	if (!list)
		parse_fatal_error();
	list->next = *get_ast_list();
	*get_ast_list() = list;
	return (list);
}

t_parse_ast	*parse_new_ast(t_parse_ast_type type, void *content)
{
	t_parse_ast_list	*list;

	if (!(type > ASTNODE_NONE && type < ASTNODE_INVALID) || !content)
		parse_fatal_error();
	list = create_ast();
	list->ast.error = 0;
	list->ast.heredocs = NULL;
	list->ast.type = type;
	list->ast.content.void_ptr = content;
	return (&list->ast);
}

