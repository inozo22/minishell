/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:59:02 by nimai             #+#    #+#             */
/*   Updated: 2023/05/17 16:28:06 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../inc/parse.h"

void	parse_die(void)
{
	int	*ptr;

	ptr = NULL;
	ptr[0] = 0xD1E;
}

void	parse_skip_spaces(t_parse_buffer *buf, t_token *tok)
{
	while (1)
	{
		if (tok->type != TOKTYPE_SPACE)
			break ;
		lex_get_token(buf, tok);
	}
}

void	parse_fatal_error(void)
{
	exit(1);
}
