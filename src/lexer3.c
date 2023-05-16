/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:34:31 by nimai             #+#    #+#             */
/*   Updated: 2023/05/16 12:39:22 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "minishell.h"

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
