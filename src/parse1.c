/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:48:57 by nimai             #+#    #+#             */
/*   Updated: 2023/05/17 15:16:59 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parse_ast *parse_cmd_line(t_parse_buffer *buf, t_token *tok)
{
	t_parse_ast				*ret;
	t_parse_ast				*seqcmd_node;
	t_parse_node_cmdline	*content;

	seqcmd_node = parse_sequential_cmd(buf, tok);
}

t_parse_ast	*parse_sequential_cmd(t_parse_buffer *buf, t_token *tok)
{
	t_parse_ast				*ret;
	t_parse_ast				*pipcmd;
	t_parse_ast				*rest;
	t_parse_node_seqcmds	*content;

	parse_skip_spaces(buf, tok);
	pipcmd = parse_piped_cmd(buf, tok);
}
