/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:41:32 by nimai             #+#    #+#             */
/*   Updated: 2023/05/16 17:40:44 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../inc/parse.h"

int	lex_getc(t_parse_buffer *buf)
{
	if (buf->getc)
		return (buf->getc(buf));
	if (buf->cur_pos == buf->size)
		return (EOF);
	return (buf->buffer[buf->cur_pos++]);
}

void	lex_ungetc(t_parse_buffer *buf)
{
	if (buf->ungetc)
	{
		buf->ungetc(buf);
		return ;
	}
	buf->cur_pos--;
}

int	lex_get_symbols(t_parse_buffer *buf, t_token *tok, int ch)
{
	if (ch == ';')
		tok->type = TOKTYPE_SEMICOLON;
	else if (ch == '|')
		tok->type = TOKTYPE_PIPE;
	else if (ch == '<' || ch == '>')
		lex_get_lt_gt(buf, tok, ch);
	else
		return (0);
	return (1);
}

int	lex_get_quoted(t_parse_buffer *buf, t_token *tok, int ch)
{
	if (buf->lex_stat != LEXSTAT_NOMAL)
		parse_die();
	if (ch == '"')
	{
		buf->lex_stat = LEXSTAT_DOUBLE_QUOTED;
		tok->type = TOKTYPE_EXPANDABLE_QUOTED;
		return (lex_read_double_quoted(buf, tok));
	}
	if (ch == '\'')
	{
		buf->lex_stat = LEXSTAT_SINGLE_QUOTED;
		tok->type = TOKTYPE_NON_EXPANDABLE;
		return (lex_read_single_quoted(buf, tok));
	}
	return (0);
}

int	lex_get_token(t_parse_buffer *buf, t_token *tok)
{
	int	ch;

	if (buf->lex_stat == LEXSTAT_NOMAL)
	{
		ch = lex_getc(buf);
		if (lex_get_spaces(buf, ret, ch) || lex_get_symbols(buf, tok, ch)|| lex_get_quoted(buf, tok, ch)|| lex_get_eof(tok, ch))
			return (1);
		tok->type = TOKTYPE_EXPANDABLE;
		lex_ungetc(buf);
		return (lex_read_word(buf, tok) && (lex_check_redirection_fd(buf, tok) || 1))
	}
}
