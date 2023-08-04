/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 18:39:55 by bde-mada          #+#    #+#             */
/*   Updated: 2023/08/04 13:58:14 by nimai            ###   ########.fr       */
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
	if (*str == '(' || *str == ')' || *str == ';' || *str == '\\' || *str == '*')
		return (INVALID);
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
	if (*str == '|')
		return (PIPE_LINE);
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

int get_token(t_list **list, char *input, int *pos)
{
	char	*token;
	t_list	*new;
	t_list	*tmp;
	int		max_pipe;

	if (pos[2] != WORD)
		pos[0]++;
	while (ft_isspace(input[pos[0]]))
		pos[0]++;
	pos[1] = pos[0];
	while (input[pos[1]])
	{	
		if (!is_quote(input[pos[1]]))
		{
			if (is_metacharacter(&input[pos[1]]) != WORD)
				break ;
			else if (is_metacharacter(&input[pos[1]]) == INVALID)
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
//	token = clear_trailing_spaces(token);
//現在、トークンは保存されずに最も後ろに記載されたものだけが実行されている。
//実行の順については要確認。
//ちなみに、ミニシェルから出る際になぜか入力済みのコマンドのエラーが出力される。
	printf("new_token: %s\n", token);
	if (!token)
		return (-1);
	while (tmp)
	{
		if (tmp->cmd_pos > max_pipe)
			max_pipe = tmp->cmd_pos;
		tmp = tmp->next;
	}
	if (pos[2] == PIPE_LINE)
		++max_pipe;
	new = ft_lstnew(token, pos[2], max_pipe);
//	ft_printf("token: %s, type: %d, pos: %d\n\n", new->content, new->type, new->cmd_pos);
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
 */
int lexer(char *input, t_list **token_list)
{
	int		i;
	int		pos[4];

	*token_list = NULL;
	i = -1;
	ft_bzero(pos, 4 * sizeof(int));
	while (input[++i])
	{
		printf("input: %s\n", &(input[i]));
		if (ft_isspace(input[i]))
			continue;
		pos[2] = is_metacharacter(&(input[i]));
		if (pos[2] == INVALID)
			return (ft_lstclear(token_list, free), -1);
		if (pos[2] != IS_SPACE)
			pos[0] = i;
		if (pos[2] == HERE_DOC || pos[2] == APPEND || (pos[2] == PIPE_LINE && input[i + 1] == input[i]))
			pos[0]++;
		ft_printf("string start: %d, type: %d\n", pos[0], pos[2]);
		pos[3] = get_token(token_list, input, pos);
		if (pos[3] == -1)
			return (ft_lstclear(token_list, free), -1);
		ft_printf("string end: %d\n", pos[1]);
		i = pos[1] - 1;
	}
	return (pos[3]);
}
