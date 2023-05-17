/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:17:24 by nimai             #+#    #+#             */
/*   Updated: 2023/05/17 17:30:45 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parse_ast	*parse_args(t_parse_buffer *buf, t_token *tok)
{
	t_parse_ast				*str;
	t_parse_ast				*redir;
	t_parse_ast				*rest;
	t_parse_node_arguments	*content;
	t_parse_ast				*args;

	rest = NULL;
	parse_skip_spaces(buf, tok);
	redir = parse_redirection(buf, tok);
	str = parse_str(buf, tok);
	if (!redir || !str)//memory free??????????
		return (NULL);
	rest = parse_args(buf, tok);
	content = mallloc(sizeof(t_parse_node_arguments));
	if (!content)//it has been created by me
		return (NULL);
	args = parse_new_ast(ASTNODE_ARGUMENTS, content);
	content->string_node = str;
	content->redirection_node = redir;
	content->rest_node = rest;
	args->error = args->error || (redir && redir->error);
	args->error = args->error || (str && str->error);
	args->error = args->error || (rest && rest->error);
	args->heredocs = parse_concat_heredocs(redir, rest);
	return (args);
/**
 * 
 * hasta aquí
 * parse_concat_heredocs done
 * 
*/


}

t_parse_ast	*parse_str(t_parse_buffer *buf, t_token *tok)
{
	t_parse_ast			*new;
	t_parse_node_string	*str;
	char				*text;
	t_token_type		type;

	type = tok->type;
	if (type != TOKTYPE_EXPANDABLE && type != TOKTYPE_NON_EXPANDABLE && type != TOKTYPE_EXPANDABLE_QUOTED)
		return (NULL);
	str = malloc(sizeof(t_parse_node_string));
	if (!str)
		parse_fatal_error();//I think I have to free memory
	new = parse_new_ast(ASTNODE_STRING, str);
	text = malloc(tok->len + 1);
	if (!text)
		parse_fatal_error();//I think I have to free memory
	str->type = type;
	ft_memcpy(text, tok->text, tok->len);
	text[tok->len] = '\0';
	str->text = text;
	lex_get_token(buf, tok);
	str->next = parse_str(buf, tok);
	return (new);
}

t_parse_ast	*parse_piped_cmd(t_parse_buffer *buf, t_token *tok)
{
	t_parse_ast				*ret;
	t_parse_node_pipcmds	*content;
	t_parse_ast				*cmd;
	t_parse_ast				*rest;

	cmd = parse_cmd(buf, tok);
}

t_parse_ast	*parse_cmd(t_parse_buffer *buf, t_token tok)
{
	t_parse_ast				*cmd;
	t_parse_node_command	*content;
	t_parse_ast				*args;

	args = parse_args(buf, tok);
}

t_parse_ast	*parse_redirection(t_parse_buffer *buf, t_token *tok)
{
	t_parse_ast					*ret;
	t_parse_ast					*str;
	t_parse_node_redirection	*redirection;
	t_token_type				*type;
	int							fd;

	type = tok->type;
	if (type != TOKTYPE_INPUT_REDIRECTION && type != TOKTYPE_HEREDOCUMENT && type != TOKTYPE_OUTPUT_REDIRECTION && type != TOKTYPE_OUTPUT_APPENDING)
		return (NULL);
	fd = tok->len;
	lex_get_token(buf, tok);
	parse_skip_spaces(buf, tok);
	str = parse_str(buf, tok);
	redirection = malloc(sizeof(t_parse_node_redirection));
	redirection->type = type;
	redirection->fd = fd;
	redirection->string_node = str;
	ret = parse_new_ast(ASTNODE_REDIRECTION, redirection);
	ret->error = !str || str->error;
	if (type == TOKTYPE_HEREDOCUMENT)
		ret->heredocs = parse_new_heredocs(redirection);
	return (ret);
}
