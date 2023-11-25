/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-mada <bde-mada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 18:39:55 by bde-mada          #+#    #+#             */
/*   Updated: 2023/10/06 16:44:15 by bde-mada         ###   ########.fr       */
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
		{
			quotes = 0;
		}
	}
	return (quotes);
}

static int	check_literal_metacharacter(int c)
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
		return (PIPE);
	if (ft_isspace(*str))
		return (IS_SPACE);
	return (WORD);
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
		;
	pos[0] = i;
	i = ft_strlen(token);
	while (i >= 0 && ft_isspace(token[--i]))
		pos[1] = i;
	new_token = ft_substr(token, pos[0], pos[1]);
	return (new_token);
}

/**
 * @note To implement avoidance of leading invisible spaces in mac:
 * while (input[pos[0]] == -62 && input[pos[0] + 1] == -96)
 * 	pos[0] += 2;
*/

/**
 * @note pos[2] = -1 is word
  */
int get_token(t_list **list, char *input, int *pos)
{
	char	*token;
	t_list	*new;
	t_list	*tmp;
	int		max_pipe;
	int		current_char_type;

	if (pos[2] != WORD)
		pos[0]++;
	while (ft_isspace(input[pos[0]]))
		pos[0]++;
	if (pos[2] == '|' && input[pos[0]] == '|')
	{
		g_return_val = error_msg("|", 2);
		return (-1);
	}
	pos[1] = pos[0];
	while (input[pos[1]])
	{	
		if (!is_quote(input[pos[1]]))
		{
			current_char_type = is_metacharacter(&input[pos[1]]);
			if (current_char_type != WORD)
				break ;
			else if (current_char_type == INVALID)
				return (1);
		}
		pos[1]++;
	}
//	ft_printf("pos[0]: %d, pos[1]: %d\n", pos[0], pos[1]);
	token = ft_substr(input, pos[0], pos[1] - pos[0]);
	if (!token)
		return (1);
//	ft_printf("str: %s\n", token);
	tmp = *list;
	max_pipe = 0;
	printf("new_token: %s\n", token);
	if (!token)
		return (-1);
	while (tmp)
	{
//		ft_printf("Line: %d token: %s, type: %d, pos: %d\n", __LINE__, tmp->content, tmp->type, tmp->cmd_pos);
		if (tmp->cmd_pos > max_pipe)
			max_pipe = tmp->cmd_pos;
		tmp = tmp->next;
	}
	if (pos[2] == PIPE)
		++max_pipe;
	new = ft_lstnew(token, pos[2], max_pipe);
	ft_printf("token: %s, type: %d, pos: %d\n", new->content, new->type, new->cmd_pos);
	if (!new)
		return (-1);
	ft_lstadd_back(list, new);
	return (max_pipe);
}



/**
 * @param pos[0] start index
 * @param pos[1] end index
 * @param pos[2] type
 * @param pos[3] max_pipe4
 * @note invalid (, ), ;, \, *
 */
int lexer(char *input, t_list **token_list)
{
	int		i;
	int		pos[4];
	t_list	*tmp;

	*token_list = NULL;
	i = -1;
	ft_bzero(pos, 4 * sizeof(int));
	ft_printf(COLOR_ACCENT"LEXER START\n"COLOR_RESET);
	if (check_valid_input(input))
		return (-1);
	i = -1;
	while (input && input[++i])
	{
		if (ft_isspace(input[i]))
			continue;
		pos[2] = is_metacharacter(&(input[i]));
		if (pos[2] == INVALID)
		{
			return (ft_lstclear(token_list, free), -1);
		}
		if (pos[2] != IS_SPACE)
			pos[0] = i;
		if (pos[2] == HERE_DOC || pos[2] == APPEND || (pos[2] == PIPE && input[i + 1] == input[i]))
			pos[0]++;
		ft_printf("string start: %d, type: %d\n", pos[0], pos[2]);
		pos[3] = get_token(token_list, input, pos);
		if (pos[3] == -1)
			return (ft_lstclear(token_list, free), -1);
//		ft_printf("string end: %d\n", pos[1]);
		i = pos[1] - 1;
	}
	tmp = *token_list;
	while (tmp)
	{
		printf("%sLEXER: Line: %d, content: %s, type: %d, pos: %d%s\n", COLOR_GREEN, __LINE__, tmp->content, tmp->type, tmp->cmd_pos, COLOR_RESET);
		tmp = tmp->next;
	}
	return (pos[3]);
}
//	printf("%sLine: %d::%s%s\n", COLOR_RED, __LINE__, __FILE__, COLOR_RESET);