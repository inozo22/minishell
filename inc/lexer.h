/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:32:34 by nimai             #+#    #+#             */
/*   Updated: 2023/05/15 17:38:50 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	LEXER_H
# define LEXER_H

typedef struct s_parse_buffer	t_parse_buffer;

typedef enum e_token_type
{
	TOKTYPE_EOF = -1,
	TOKTYPE_PARSE_ERROR = 0,
	TOKTYPE_NON_EXPANDABLE = 0xc101,
	TOKTYPE_EXPANDABLE,
	TOKTYPE_EXPANDABLE_QUOTED,
	TOKTYPE_PIPE,
	TOKTYPE_INPUT_REDIRECTION,
	TOKTYPE_HEREDOCUMENT,
	TOKTYPE_OUTPUT_REDIRECTION,
	TOKTYPE_OUTPUT_APPENDING,
	TOKTYPE_SEMICOLON,
	TOKTYPE_NEWLINE,
	TOKTYPE_SPACE,
}	t_token_type;

typedef enum e_lexer_state
{
	LEXSTAT_NOMAL = 0xd101,
	LEXSTAT_SINGLE_QUOTED,
	LEXSTAT_DOUBLE_QUOTED,		
}	t_lexer_state;

typedef struct s_token
{
	char			*text;
	int				len;
	int				max_len;
	t_token_type	type;
}


#endif