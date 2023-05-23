/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:48:57 by nimai             #+#    #+#             */
/*   Updated: 2023/05/18 17:03:44 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parse_ast	*parse_cmd_line(t_parse_buffer *buf, t_token *tok)
{
	t_parse_ast				*ret;
	t_parse_ast				*seqcmd_node;
	t_parse_node_cmdline	*content;

	seqcmd_node = parse_sequential_cmd(buf, tok);
	if (!seqcmd_node)
		return (NULL);
	parse_skip_spaces(buf, tok);
	if (tok->type != TOKTYPE_NEWLINE)
		return (NULL);
	content = malloc(sizeof(t_parse_node_cmdline));
	if (!content)
		return (NULL);//I put this, maybe it's necessary to free?
	ret = parse_new_ast(ASTNODE_COMMAND_LINE, content);
	content->seqcmd_node = seqcmd_node;
	ret->error = ret->error || seqcmd_node->error;
	if (ret->error)
		return (NULL);
	ret->heredocs = seqcmd_node->heredocs;
	return (ret);
}

t_parse_ast	*parse_delimiter(t_parse_buffer *buf, t_token *tok)
{
	t_parse_ast				*ret;
	t_parse_node_delimiter	*content;

	parse_skip_spaces(buf, tok);
	if (tok->type != TOKTYPE_SEMICOLON)
		return (NULL);
	content = malloc(sizeof(t_parse_node_delimiter));
	ret = parse_new_ast(ASTNODE_DELIMITER, content);
	content->type = TOKTYPE_SEMICOLON;
	return (ret);
}

t_parse_ast	*parse_sequential_cmd(t_parse_buffer *buf, t_token *tok)
{
	t_parse_ast				*ret;
	t_parse_ast				*pipcmd;
	t_parse_ast				*rest;
	t_parse_node_seqcmds	*content;

	parse_skip_spaces(buf, tok);
	pipcmd = parse_piped_cmd(buf, tok);
	if (!pipcmd)
		return (NULL);//free??
	content = malloc(sizeof(t_parse_node_seqcmds));
	ret = parse_new_ast(ASTNODE_SEQ_COMMANDS, content);
	content->pipcmd_node = pipcmd;
	content->delimiter_node = parse_delimiter(buf, tok);
	rest = NULL;
	if (content->delimiter_node)
	{
		lex_get_token(buf, tok);
		parse_skip_spaces(buf, tok);
		rest = parse_sequential_cmd(buf, tok);
	}
	content->rest_node = rest;
	ret->error = ret->error || pipcmd->error;
	ret->error = ret->error || (rest && rest->error);
	ret->heredocs = parse_concat_heredocs(pipcmd, rest);
	return (ret);
}
