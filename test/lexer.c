/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 18:39:55 by bde-mada          #+#    #+#             */
/*   Updated: 2023/08/03 16:20:16 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libft/libft.h"

//tokens: | ; < > >> << () \

int errors(int error_id)
{
	ft_putstr_fd("minishell: invalid metacharacter: ", 2);
	ft_putchar_fd(error_id, 2);
	ft_putchar_fd('\n', 2);
	return (1);
	
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putchar_fd(error_id, 2);
	ft_putendl_fd("'", 2);
	return (1);
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
int is_metacharacter(char *str)
{
	if (*str == '(' || *str == ')' || *str == ';' || *str == '\\' || *str == '*')
		return (1);
	if (*str == '<')
		if (*(str + 1) == *str)
			return (2);
		else
			return (3);
	if (*str == '>')
		if (*(str + 1) == *str)
			return (4);
		else
			return (5);
	if (*str == '|')
		return (6);
	return (0);
}

/**
 * @param pos[0] start index
 * @param pos[1] end index
*/
char	*clear_trailing_spaces(char *token)
{
	int		i;
	int		pos[2];
	char	*new_token;

	ft_bzero(pos, 2 * sizeof(int));
	i = -1;
	while (ft_isspace(token[++i]))
		pos[0] = i + 1;
	i = ft_strlen(token);
	while (ft_isspace(token[--i]))
		pos[1] = i;
	new_token = ft_substr(token, pos[0], pos[1] - pos[0]);
}

int	get_token(t_list *token, char *str)
{
	int	i;
	int	type;
	int cmd_pos;

	if (token)
		cmd_pos = token->cmd_pos;
	else
		cmd_pos = 0;

	i = 0;
	while (str[++i])
	{
		type = is_metacharacter(str[i]);
		if (type == 1)//is an invalid metacharacter
			return (-1);
		if (type == 2)//is a redirection
		{	
			ft_lstadd_back(&token, ft_lstnew(ft_substr(str, 1, i), str[0], cmd_pos));
			return (i);
		}
		if (type == 3)//is a pipe
		{
			ft_lstadd_back(&token, ft_lstnew(ft_substr(str, 1, i), str[0], cmd_pos + 1));
			return (i);
		}
	}
	ft_lstadd_back(&token, ft_lstnew(ft_substr(str, 1, i), str[0], cmd_pos + 1));
	return (i);
	
}

int	lexer(char *input)
{
	t_list	*token_list;
	int		i;
	int		type;
	int		pos[3];
	
	token_list = NULL;
	i = -1;
	ft_bzero(pos, 3 * sizeof(int));
	while (input[++i])
	{
		type = is_metacharacter(input[i]);
		if (type == 1)
			return ((int) ft_lstclear(&token_list, free));
		if (type == 2)
		{
			if (is_metacharacter(input[i + 1]) == 2)
				i += get_token(token_list, input + i);
			else
				i += get_token(token_list, input + i);
		}
			while (*input)
			{
				++input;
				if (is_metacharacter(*input) == 2)
				{
					ft_lstadd_back(&token_list, ft_lstnew(ft_substr(input, 0, 2)));
				}
					return ((int) ft_lstclear(&token_list, free));
			}
		else
			input++;
	}
	
}

int	main(int ac, char **av)
{
	t_list	*tokens;

	tokens = lexer(av[1]);
	if (!tokens)
		return (errors('&'));
	while (tokens)
	{
		ft_printf("Content: %s, type: %c\n", tokens->content, tokens->type);
		tokens = tokens->next;
	}
	ft_lstclear(&tokens, free);
}