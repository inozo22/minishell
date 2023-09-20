/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-mada <bde-mada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 18:39:55 by bde-mada          #+#    #+#             */
/*   Updated: 2023/09/18 16:31:49 by bde-mada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* tokens: | ; < > >> << () \ */

/* int errors(int error_id)
{
	ft_putstr_fd("minishell: invalid metacharacter: ", 2);
	ft_putchar_fd(error_id, 2);
	ft_putchar_fd('\n', 2);
	return (1);
	
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putchar_fd(error_id, 2);
	ft_putendl_fd("'", 2);
	return (1);
} */

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

int	count_tokens(char *str)
{
	int count;
	int in_token;
	int	quotes;
	
	in_token = 0;
	while (*str)
	{
		quotes
		if (is_quote(*str))
		if (is_metacharacter(str))
			count++;
			in_token = 0;
		else
			in_token = 1;
		str++;
	}
	return (count);
	
}

int	lexer(char *input, t_list **token_list)
{
	
}
