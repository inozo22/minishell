/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:51:59 by nimai             #+#    #+#             */
/*   Updated: 2023/05/16 13:56:14 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"

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

