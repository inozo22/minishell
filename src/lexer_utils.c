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
