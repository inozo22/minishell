/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:41:32 by nimai             #+#    #+#             */
/*   Updated: 2023/05/16 13:57:27 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"

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

int	lex_get_token(t_parse_buffer *buf, t_token *tok)
{
	int	ch;

	if (buf->lex_stat == LEXSTAT_NOMAL)
	{
		ch = lex_getc(buf);
		if (lex_get_spaces(buf, ret, ch) || lex_get_symbols(buf, tok, ch)|| lex_get_quoted(buf, tok, ch)|| lex_get_eof(tok, ch))
			return (1);
	}
}
