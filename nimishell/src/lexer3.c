/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-mada <bde-mada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 18:39:55 by bde-mada          #+#    #+#             */
/*   Updated: 2023/10/12 18:32:22 by bde-mada         ###   ########.fr       */
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

//DELETE GLOBAL VARIABLE SET HERE
//extern volatile int g_return_val = 0;

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
		return (PIPE);
	if (ft_isspace(*str))
		return (IS_SPACE);
	if (*str == '\"' || *str == '\'')
		return (QUOTE);
	return (WORD);
}

/* int	count_tokens(char *str)
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
} */
/**
 * @note check if there are open quotes in string
 * @return 0 if there are no open quotes
 */
static int	check_quotes_in_string(char *str)
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

static int	end_with_pipe(char *str)
{
	int	pipe_flag;

	pipe_flag = 0;
	while (*str)
	{
		if (*str == '|')
			pipe_flag = 1;
		else if (!ft_isspace(*str))
			pipe_flag = 0;
		str++;
	}
	return (pipe_flag);
}

static char	*dquote(char *input)
{
	char	*tmp[2];
	int		i;

	ft_bzero(tmp, 2 * sizeof(char *));
	i = 0;
//	ft_printf("Input in dquote: %s\n", input);
	while (check_quotes_in_string(input) || end_with_pipe(input))
	{
		tmp[0] = readline(">");
		tmp[1] = input;
		input = ft_strjoin(input, tmp[0]);
		free(tmp[0]);
		if (i == 1)
			free(tmp[1]);
		i = 1;
	}
//	ft_printf("output in dquote: %s\n", input);
	return (input);
}

/**
 * @return -1 if there is an error
 * @param i[0] start index
 * @param i[1] end index
 * @param i[2] type
 * @param i[3] quotes flag
 */
int	get_node(char *str, t_list **list, int max_pipe)
{
	int		i[4];
	char 	*token;
	t_list	*new_node;

//	ft_printf("str: %s\n", str);
	ft_bzero(i, 4 * sizeof(int));
	i[2] = is_metacharacter(str);
	if (i[2] == INVALID)
	{
		//DELETE and set error message
//		ft_printf("invalid metacharacter\n");
		return (-1);
	}
	if (i[2] != WORD && i[2] != QUOTE)
	{
		//DELETE
//		ft_printf("Hey1\n");
		i[0]++;
	}
	if (i[2] == HERE_DOC || i[2] == APPEND \
		|| (i[2] == REDIR_OUT && *(str + 1) == PIPE))
	{
		//DELETE
//		ft_printf("Hey2\n");
		i[0]++;
	}
	while (ft_isspace(str[i[0]]))
	{
		//DELETE
//		ft_printf("Hey3\n");
		i[0]++;
	}
	i[1] = i[0];
	while (str[i[1]] && (is_metacharacter(str + i[1]) == WORD
			|| is_quote(str[i[1]])))
	{
//		ft_printf("Quotes status: %d\n", i[3]);
//		ft_printf("str[%d]: %c\n", i[1], str[i[1]]);
		i[1]++;
	}
	if (str[i[1]] == QUOTE || str[i[1]] == DOUBLE_QUOTE)
		i[1]++;
//	ft_printf("start: %d, end: %d\n", i[0], i[1]);
	if (i[1] == i[0])
	{
		//DELETE and set error message
		if (i[2] == PIPE && str[i[1]] != PIPE)
			return (1);
//		ft_printf("contiguous metacharacters\n");
		return (-1);	
	}
	token = ft_substr(str, i[0], i[1] - i[0]);
	new_node = ft_lstnew(token, i[2], max_pipe);
//	ft_printf("token: %s, type: %d, pos: %d\n", new_node->content, new_node->type, new_node->cmd_pos);
	if (!new_node)
		return (-1);
	ft_lstadd_back(list, new_node);
	return (i[1]);
}

/**
 * @param i[0] current start index
 * @param i[1] current end index
 * @note if i[1] = -1, then there is an error
 * @param i[2] max pipe
 * @note invalid (, ), ;, \, *
 */
int	lexer(char *input, t_list **token_list)
{
	int	i[3];
	//DELETE
	t_list *tmp;

	*token_list = NULL;
	ft_bzero(i, 3 * sizeof(int));
	input = dquote(input);
	
	while (input[i[0]])
	{
		//DELETE		
//		ft_printf("Current status: %s\n", input + i[0]);
		if (input[i[0]] == PIPE && *token_list == NULL)
		//CHECK CORRECT MESSAGE
		{
			g_return_val = error_msg("|", 2);
			return (-1);
		}
		if (!ft_isspace(input[i[0]]))
		{
			if (input[i[0]] == PIPE)
				i[2]++;
			i[1] = get_node(input + i[0], token_list, i[2]);
			//DELETE
//			ft_printf("i[1]: %d\n", i[1]);
			if (i[1] == -1)
				return (-1);
			i[0] += i[1];
		}
		else
			i[0]++;
	}
	tmp = *token_list;
	while (tmp)
	{
		printf("%sLEXER: Line: %d, content: %s, type: %d, pos: %d%s\n", COLOR_GREEN, __LINE__, tmp->content, tmp->type, tmp->cmd_pos, COLOR_RESET);
		tmp = tmp->next;
	}
	return (i[2]);
}

/* int	main(int argc, char **argv)
{
	t_list	*token_list;
	t_list	*tmp;
	int		i;

	i = 0;
	if (argc != 2)
		return (0);
	if (lexer(argv[1], &token_list) == -1)
		return (ft_lstclear(&token_list, free), -1);
	tmp = token_list;
	while (tmp)
	{
		printf("%sLEXER: Line: %d, content: %s, type: %d, pos: %d%s\n", COLOR_GREEN, __LINE__, tmp->content, tmp->type, tmp->cmd_pos, COLOR_RESET);
		tmp = tmp->next;
	}
	ft_lstclear(&token_list, free);
	return (0);
} */

// cc -Wall -Wextra -g3 -fsanitize=address lexer3.c lexer_utils.c error_msgs.c terminate.c -L../lib/libft -lft -I../include -I../lib/libft  && ./a.out
