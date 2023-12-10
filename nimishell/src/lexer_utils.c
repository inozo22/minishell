/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-mada <bde-mada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 18:24:57 by bde-mada          #+#    #+#             */
/*   Updated: 2023/12/10 18:14:48 by bde-mada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	literal_metacharacters_used(char *str)
{
	char	meta_chars[12];
	int		i;
	
	i = -1;
	ft_bzero(meta_chars, 12);
	while (*str)
	{
		if (check_literal_metacharacter(*str) && !ft_strchr(meta_chars, *str))
		{
			while(meta_chars[++i])
				;
			meta_chars[i] = *str;
		}
		str++;
	}
	if (meta_chars[0])
	{
		ft_printf(COLOR_YELLOW"Used metachars: %s\n"COLOR_RESET, meta_chars);
		ft_putstr_fd("Special characters like (), [], {}, *, \\, &, ``...", 1);
		ft_putendl_fd(" will be treated as literal\n", 1);
		return (1);
	}
	return (0);
}

int	check_literal_metacharacter(int c)
{
	if (c == '(' || c == ')' || c == ';' || c == '\\' \
	|| c == '*' || c == '&' || c == '`' || c == '[' \
	|| c == ']' || c == '{' || c == '}')
	{
		return (1);
	}
	return (0);
}

int	is_quote(char c)
{
	static char	quotes = 0;

	if (c == '\'' || c == '\"')
	{
		if (quotes == 0)
			quotes = c;
		else if (quotes == c)
			quotes = 0;
	}
	return (quotes);
}

/**
 * @return 1 if c is an invalid metacharacter
 * @return 2 if c is a redirection
 * @return 3 if c is a pipe
 */
int	is_metacharacter(char *str)
{
	if (check_literal_metacharacter(*str))
		return (WORD);
	if (*str == '<')
	{
		if (*(str + 1) == *str)
			return (HERE_DOC);
		else
			return (REDIR_IN);
	}
	if (*str == '>')
	{
		if (*(str + 1) == *str)
			return (APPEND);
		else
			return (REDIR_OUT);
	}
	if (*str == '|' && *(str + 1) == '|')
		return (INVALID);
	if (*str == '|')
		return (PIPE);
	if (ft_isspace(*str))
		return (IS_SPACE);
	if (*str == '\"' || *str == '\'')
		return (QUOTE);
	return (WORD);
}

/**
 * @note check if there are open quotes in string
 * @return 0 if there are no open quotes
 */
int	check_quotes_in_string(char *str)
{
	int	qutoes_flag;

	qutoes_flag = is_quote(*str);
	is_quote(qutoes_flag);
	qutoes_flag = 0;
	while (*str)
	{
		qutoes_flag = is_quote(*str);
		str++;
	}
	if (qutoes_flag)
		return (1);
	return (0);
}
