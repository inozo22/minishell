/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 18:39:55 by bde-mada          #+#    #+#             */
/*   Updated: 2023/12/11 13:14:26 by nimai            ###   ########.fr       */
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

	ft_bzero(tmp, 2 * sizeof(char *));
	while (check_quotes_in_string(input) || end_with_pipe(input))
	{
		tmp[0] = readline(">");
		tmp[1] = input;
		input = ft_strjoin(input, tmp[0]);
		free(tmp[0]);
		free(tmp[1]);
	}
	return (input);
}

/**
 * Get start and end of the node and check contiguous metacharacters 
 */
static int	get_node_values(char *str, int *i)
{
	ft_bzero(i, 4 * sizeof(int));
	i[2] = is_metacharacter(str);
	if (i[2] == INVALID)
		return (-1);
	if (i[2] != WORD && i[2] != QUOTE)
		i[0]++;
	if (i[2] == HERE_DOC || i[2] == APPEND)
		i[0]++;
	while (ft_isspace(str[i[0]]))
		i[0]++;
	i[1] = i[0];
	while (str[i[1]] && (is_quote(str[i[1]]) \
			|| (is_metacharacter(str + i[1]) == WORD \
			|| is_metacharacter(str + i[1]) == QUOTE)))
		i[1]++;
	if (str[i[1]] == QUOTE || str[i[1]] == DOUBLE_QUOTE)
		i[1]++;
	return (i[1]);
}

/**
 * @return -1 if there is an error
 * @return 1 if there is a metacharacter after pipe
 * @param i[0] start index
 * @param i[1] end index
 * @param i[2] type
 * @param i[3] quotes flag
 */
static int	get_node(char *str, t_list **list, t_data *data, int max_pipe)
{
	int		i[4];
	char	*token;
	t_list	*new_node;

	get_node_values(str, i);
	if (i[1] == i[0])
	{
		if (i[2] == PIPE && str[i[1]] != PIPE)
			return (1);
		if ((str[i[1]] == REDIR_IN || str[i[1]] == REDIR_OUT) \
			&& str[i[1]] == str[i[1] + 1])
			token = ft_substr(str, i[0], 2);
		else
			token = ft_substr(str, i[0], 1);
		data->return_val = error_msg(token, 2);
		free(token);
		return (-1);
	}
	token = ft_substr(str, i[0], i[1] - i[0]);
	new_node = ft_lstnew(token, i[2], max_pipe);
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
int	lexer(char *input, t_list **token_list, t_data *data)
{
	int		i[3];
	char	*input_tmp;

	input_tmp = ft_strdup(input);
	ft_bzero(i, 3 * sizeof(int));
	if (input_tmp[i[0]] == PIPE)
		return (free(input_tmp), data->return_val = error_msg("|", 2), -1);
	input_tmp = dquote(input_tmp);
	literal_metacharacters_used(input_tmp);
	while (input_tmp[i[0]])
	{
		if (!ft_isspace(input_tmp[i[0]]))
		{
			if (input_tmp[i[0]] == PIPE)
				i[2]++;
			i[1] = get_node(input_tmp + i[0], token_list, data, i[2]);
			if (i[1] == -1)
				return (ft_lstclear(token_list, free), free(input_tmp), -1);
			i[0] += i[1];
		}
		else
			i[0]++;
	}
	return (free (input_tmp), i[2]);
}
	//DELETE
/* 	t_list *tmp = *token_list;
	while (tmp)
	{
		printf("%sLEXER: content: %s, type: %d, pos: %d%s\n", COLOR_GREEN, \
				tmp->content, tmp->type, tmp->cmd_pos, COLOR_RESET);
		tmp = tmp->next;
	} */

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
