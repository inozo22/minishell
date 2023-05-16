/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:06:24 by nimai             #+#    #+#             */
/*   Updated: 2023/05/16 14:57:06 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../inc/parse.h"

void	lex_get_lt_gt(t_parse_buffer *buf, t_token *tok, int ch)
{
	if (ch == '<')
	{
		ch = lex_getc(buf);
		if (ch == '<')
			tok->type = TOKTYPE_HEREDOCUMENT;
		else
		{
			lex_ungetc(buf);
			tok->type = TOKTYPE_INPUT_REDIRECTION;
		}
		tok->len = 0;
	}
	else
	{
		ch = lex_getc(buf);
		if (ch == '>')
			tok->type = TOKTYPE_OUTPUT_APPENDING;
		else
		{
			tok->type = TOKTYPE_OUTPUT_REDIRECTION;
			if (ch != EOF)
				lex_ungetc(buf);
		}
		tok->len = 1;
	}
}
