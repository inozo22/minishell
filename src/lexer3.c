/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:34:31 by nimai             #+#    #+#             */
/*   Updated: 2023/05/17 13:39:42 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parse.h"
#include "minishell.h"

bool	is_int_overflow(char *num)
{
	long	nb;

	nb = ft_atoi(num);
	if (nb > 2147483647 || nb < -2147483648)
		return (true);
	return (false);
}

int	lex_check_redirection_fd(t_parse_buffer *buf, t_token *tok)//5/17 he eliminado fd, porque no veo la necesidad
{
	int	i;
	int	ch;

	i = 0;
	while (i < tok->len)
	{
		if (!ft_isdigit(tok->text[i]))
			return (0);
		i++;
	}
	tok->text[i] = '\0';
	ch = lex_getc(buf);
	if ((ch == '<' || ch == '>') && !is_int_overflow(tok->text))
	{
		lex_get_symbols(buf, tok, ch);
		tok->len = ft_atoi(tok->text);
	}
	else
		lex_ungetc(buf);
	return (1);
}

int	lex_escaped(t_parse_buffer *buf, t_token *tok)
{
	char	ch;

	ch = lex_getc(buf);
	if (ch == '\\')
	{
		ch = lex_getc(buf);
		if (ch != '\n' && (buf->lex_stat == LEXSTAT_NOMAL || (buf->lex_stat == LEXSTAT_DOUBLE_QUOTED && ft_strchr("$\"\'\\`", ch))))
		{
			tok->text[0] = ch;
			tok->len = 1;
			tok->type = TOKTYPE_NON_EXPANDABLE;
			return (1);
		}
		lex_ungetc(buf);
		tok->text[0] = '\\';
		tok->len = 1;
		tok->type = TOKTYPE_NON_EXPANDABLE;
		return (1);
	}
	lex_ungetc(buf);
	return (0);
}

int	lex_get_eof(t_token *tok, int ch)
{
	if (ch == EOF)
	{
		tok->type = TOKTYPE_EOF;
		return (1);
	}
	return (0);
}

int	lex_init_token(t_token *tok)
{
	tok->max_len = 1024;
	tok->text = malloc(tok->max_len);
	if (!tok->text)
	{
		printf("malloc token buffer failed\n");
		exit(1);
	}
	tok->len = 0;
	tok->type = TOKTYPE_PARSE_ERROR;
	return (0);
}
