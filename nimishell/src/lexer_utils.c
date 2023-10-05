/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-mada <bde-mada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 18:24:57 by bde-mada          #+#    #+#             */
/*   Updated: 2023/09/26 18:29:03 by bde-mada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_valid_input(char *input)
{
	int	i;
	// int	quotes;

	i = -1;
	// quotes = 0;
	while (input && input[++i])
	{
		if (ft_isspace(input[i]))
			continue;
		if (input[i] == '|')
		{
			g_return_val = error_msg("|", 2);
			return (1);
		}
		else
			break ;
	}
	return (0);
}

int	check_literal_metacharacter(int c)
{
	if (c == '(' || c == ')' || c == ';' || c == '\\' \
	|| c == '*' || c == '&' || c == '`' || c == '[' \
	|| c == ']' || c == '{' || c == '}')
	{
		ft_printf(COLOR_YELLOW"Used metacharacter: %c\n"COLOR_RESET, c);
		ft_putstr_fd("Special characters like (), [], {}, *, \\, &, ``...", 1);
		ft_putendl_fd(" will be treated as literal characters\n\n", 1);	
		return (1);
	}
	return (0);
}
