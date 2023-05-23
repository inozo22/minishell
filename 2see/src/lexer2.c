/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:51:59 by nimai             #+#    #+#             */
/*   Updated: 2023/05/16 17:40:41 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../inc/parse.h"

int	lex_read_word(t_parse_buffer *buf, t_token *tok)
{
	int pos;
	int ch;

	if (lex_escaped(buf, tok))
		return (1); 
	pos = 0;
	while (1)
	{
		ch = lex_getc(buf);
		if (ch == EOF)
			break ;
		if (ch == '\\' || lex_is_special_char(ch) || (ch == '$' && pos > 0))
		{
			lex_ungetc(buf);
			break ;
		}
		tok->text[pos++] = ch;
		if (pos == tok->max_len)
			lex_expand_text_buf(tok);
	}
	tok->len = pos;
	return (1);
}

int	lex_read_double_quoted(t_parse_buffer *buf, t_token *tok)
{
	int	pos;
	int	ch;

	if (lex_escaped(buf, tok))
		return (1);
	pos = 0;
	while (1)
	{
		ch = lex_getc(buf);
		if (ch == '"' || ch == '\n' || ch == EOF)
			buf->lex_stat = LEXSTAT_NOMAL;
		if (ch == '\n' || ch == EOF)
			tok->type = TOKTYPE_PARSE_ERROR;
		if (ch == '\\' || ch == '\n' || ch == EOF || (ch == '$' && pos > 0))
			lex_ungetc(buf);
		if (ch == '\\' || ch == '"' || ch == '\n' || ch == EOF || (ch == '$' && pos > 0))
			break ;
		tok->text[pos++] = ch;
		if (pos == tok->max_len)
			lex_expand_text_buf(tok);
	}
	tok->len = pos;
	return (1);
}

int	lex_read_single_quoted(t_parse_buffer *buf, t_token *tok)
{
	int	pos;
	int	ch;

	pos = 0;
	while (1)
	{
		ch = lex_getc(buf);
		if (ch == '\'' || ch == '\n' || ch == EOF)
			buf->lex_stat = LEXSTAT_NOMAL;
		if (ch == '\n' || ch == EOF)
		{
			tok->type = TOKTYPE_PARSE_ERROR;
			lex_ungetc(buf);
		}
		if (ch == '\'' || ch == '\n' || ch == EOF)
			break ;
		tok->text[pos++] = ch;
		if (pos == tok->max_len)
			lex_expand_text_buf(tok);
	}
	tok->len = pos;
	return (1);
}

int	lex_get_spaces(t_parse_buffer *buf, t_token *tok, int ch)
{
	if (ch == ' ' || ch == '\t')
	{
		while (1)
		{
			ch = lex_getc(buf);
			if (ch != EOF)
			{
				lex_ungetc(buf);
			}
			tok->type = TOKTYPE_SPACE;
			break ;
		}
		return (1);
	}
	else if (ch == '\n')
	{
		tok->type = TOKTYPE_NEWLINE;
		return (1);
	}
	return (0);
}

