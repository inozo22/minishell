/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 18:39:55 by bde-mada          #+#    #+#             */
/*   Updated: 2023/11/25 19:09:11 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* tokens: | ; < > >> << () \ */

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
	while (check_quotes_in_string(input) || end_with_pipe(input))
	{
		tmp[0] = readline(">");
		tmp[1] = input;
		input = ft_strjoin(input, tmp[0]);
		free(tmp[0]);
		// if (i == 1)
			free(tmp[1]);
		i = 1;
	}
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
	char	*token;
	t_list	*new_node;

	ft_bzero(i, 4 * sizeof(int));
	i[2] = is_metacharacter(str);
	if (i[2] == INVALID)
		return (-1);
	if (i[2] != WORD && i[2] != QUOTE)
		i[0]++;
	if (i[2] == HERE_DOC || i[2] == APPEND \
		|| (i[2] == REDIR_OUT && *(str + 1) == PIPE))
		i[0]++;
	while (ft_isspace(str[i[0]]))
		i[0]++;
	i[1] = i[0];
/* 	while (str[i[1]] && (is_metacharacter(str + i[1]) == WORD
			|| is_quote(str[i[1]]))) */
	while (str[i[1]] && (is_quote(str[i[1]]) \
			|| (is_metacharacter(str + i[1]) == WORD || is_metacharacter(str + i[1]) == QUOTE)))
		i[1]++;
	if (str[i[1]] == QUOTE || str[i[1]] == DOUBLE_QUOTE)
		i[1]++;
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
	return (ft_lstadd_back(list, new_node), i[1]);
}

/**
 * @param i[0] current start index
 * @param i[1] current end index
 * @note if i[1] = -1, then there is an error
 * @param i[2] max pipe
 * @note invalid (, ), ;, \, *
 */
int	lexer(char *input, t_list **token_list, t_data **data)
{
	int		i[3];
	char	*input_tmp = ft_strdup(input);//231125nimai added to remove memory leaks
	//DELETE
	t_list *tmp;

	*token_list = NULL;
	input_tmp = ft_strdup(input);//231125nimai added to remove memory leaks
	ft_bzero(i, 3 * sizeof(int));
	if (input_tmp[i[0]] == PIPE && *token_list == NULL)
	//CHECK CORRECT MESSAGE
	{
		(*data)->return_val = error_msg("|", 2);
		return (-1);
	}
	input_tmp = dquote(input_tmp);
	while (input_tmp[i[0]])
	{
		//DELETE		
//		ft_printf("Current status: %s\n", input + i[0]);
		if (!ft_isspace(input_tmp[i[0]]))
		{
			if (input_tmp[i[0]] == PIPE)
				i[2]++;
			i[1] = get_node(input_tmp + i[0], token_list, i[2]);
			//DELETE
//			ft_printf("i[1]: %d\n", i[1]);
			if (i[1] == -1)
				return (-1);
			i[0] += i[1];
		}
		else
			i[0]++;
	}
	//DELETE
	tmp = *token_list;
	while (tmp)
	{
		printf("%sLEXER: Line: %d, content: %s, type: %d, pos: %d%s\n", COLOR_GREEN, __LINE__, tmp->content, tmp->type, tmp->cmd_pos, COLOR_RESET);
		tmp = tmp->next;
	}
	return (free (input_tmp)/* 231125nimai added to remove memory leaks */, i[2]);
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
		printf("%sLEXER: Line: %d, content: %s, type: %d, pos: %d%s\n", \
				COLOR_GREEN, __LINE__, tmp->content, tmp->type, tmp->cmd_pos, \
				COLOR_RESET);
		tmp = tmp->next;
	}
	ft_lstclear(&token_list, free);
	return (0);
} */

// cc -Wall -Wextra -g3 -fsanitize=address lexer3.c lexer_utils.c error_msgs.c
//	terminate.c -L../lib/libft -lft -I../include -I../lib/libft  && ./a.out
