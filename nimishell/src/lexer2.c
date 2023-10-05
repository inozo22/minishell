/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-mada <bde-mada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 18:39:55 by bde-mada          #+#    #+#             */
/*   Updated: 2023/09/26 19:10:59 by bde-mada         ###   ########.fr       */
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

/**
 * @return 1 if c is an invalid metacharacter
 * @return 2 if c is a redirection
 * @return 3 if c is a pipe
 */
int is_metacharacter(char *str)
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
		return (PIPE_LINE);
	if (ft_isspace(*str))
		return (IS_SPACE);
	return (WORD);
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
/**
 * @note check if there are open quotes in string
 * @return 0 if there are no open quotes
 */
static int	check_quotes_in_string(char *str)
{	
	while (*str)
	{
		is_quote(*str);
		str++;
	}
	if (is_quote(*str))
		return (1);
	return (0);
}

static char	*dquote(char *input)
{
	char	*tmp[2];

	ft_bzero(tmp, 2 * sizeof(char *));
	ft_printf("Input in dquote: %s\n", input);
	while (check_quotes_in_string(input))
	{
		tmp[0] = readline(">");
		tmp[1] = input;
		input = ft_strjoin(input, tmp[0]);
		free(tmp[0]);
		free(tmp[1]);
	}
	ft_printf("output in dquote: %s\n", input);
	return (input);
}

int	che()
{

}

/**
 * @param pos[0] current index
 * @param pos[1] word start index
 * @param pos[2] word end index
 * @param pos[3] type
 * @param pos[4] max_pipe4
 * @note invalid (, ), ;, \, *
 */
int	lexer(char *input, t_list **token_list)
{
	int	pos[5];
	int	i;
	char	**tokens;
	//DELETE
	t_list	*tmp;

	token_list = NULL;
	i = -1;
	input = dquote(input);
	while (input[++i])
	{
		if (!ft_isspace(input[i]))
		{

		}


	}
}
