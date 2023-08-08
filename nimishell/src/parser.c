/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:43:39 by bde-mada          #+#    #+#             */
/*   Updated: 2023/08/08 13:20:40 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_quotes(char *str)
{
	int	quotes;
	int	i;

	ft_printf("Check quotes input: %s\n", str);
	quotes = 0;
	i = -1;
	while (str[++i])
	{
		if (ft_isquote(str[i]))
		{
			if (i > 0 && str[i - 1] == '\\')
				str++;
			else if (quotes == str[i])
				quotes = 0;
			else if (!quotes && str[i] == str[i + 1])
			{
				str[i] = ' ';
				str[i + 1] = ' ';
			}
			else if (!quotes)
				quotes = str[i];
		}
	}
	ft_printf("Quotes status: %c\n", quotes);
	return (quotes);
}

static char	*dquote(char *str)
{
	char	*tmp[2];

	ft_bzero(tmp, 2 * sizeof(char *));
	ft_printf("Input in dquote: %s\n", str);
	while (check_quotes(str) || !ft_strcmp(str, "\\") \
			|| str[ft_strlen(str) - 1] == '|')
	{
		tmp[0] = readline(">");
		tmp[1] = str;
		str = ft_strjoin(str, tmp[0]);
		free(tmp[0]);
		free(tmp[1]);
	};
	ft_printf("output in dquote: %s\n", str);
	return (str);
}

char	*ft_remove_char(char *str, int c)
{
	char	*char_pos;
	char	*cleaned;
	char	*tmp;

	char_pos = ft_strchr(str, c);
	cleaned = ft_substr(str, 0, str - char_pos);
	tmp = cleaned;
	cleaned = ft_strjoin(cleaned, char_pos + 1);
	free (tmp);
	return (cleaned);
}

char	*remove_quotes(char *str)
{
	char	*cleaned;

	cleaned = str;
	while (ft_strchr(cleaned, '\"'))
		ft_remove_char(cleaned, '\"');
	return (cleaned);
}

/* int	parse_special_chars(t_list **cmd, char c)
{
	int		i;
	char	*tmp;
	char	**list;
	t_list	*node;

	i = -1;
	node = *cmd;
	while (node)
	{
		ft_printf("parse initial value: %s\n", node->content);
		if (node->content[ft_strlen(node->content) - 1] == c)
		{
			error_msg("minihell", "newline", 2);
			return((long int) ft_lstclear(cmd, free));
		}
		list = ft_split(node->content, c);
		if (!list)
			return (1);
		tmp = node->content;
		node->content = list[0];
		free(tmp);
		while (list[++i])
		{
			ft_lstadd_back(&node, ft_lstnew(*list, c, i));
			node = node->next;
		}
		node = node->next;
	}
	while (ft_strchr(list[i], c))
	{
		if (ft_strlen(list[i]) == 1)
		{
			if (!list[i + 1])
				{
					error_msg("minihell", "newline", 2);
					return((long int) ft_lstclear(cmd, free));
				}
			
		}
		
	}
	return (1);
} */

int	parse_special_chars(t_list **cmd, char c)
{
	int		i;
	char	*tmp;
	char	**list;
	t_list	*node;

	i = -1;
	node = *cmd;
	while (node)
	{
		ft_printf("parse initial value: %s\n", node->content);
		if (node->content[ft_strlen(node->content) - 1] == c)
		{
			error_msg("minihell", "newline", 2);
			return((long int) ft_lstclear(cmd, free));
		}
		list = ft_split(node->content, c);
		if (!list)
			return (1);
		tmp = node->content;
		node->content = list[0];
		free(tmp);
		while (list[++i])
		{
			ft_lstadd_back(&node, ft_lstnew(*list, c, i));
			node = node->next;
		}
		node = node->next;
	}
	while (ft_strchr(list[i], c))
	{
		if (ft_strlen(list[i]) == 1)
		{
			if (!list[i + 1])
				{
					error_msg("minihell", "newline", 2);
					return((long int) ft_lstclear(cmd, free));
				}
			
		}
		
	}
	return (1);
}

int	parse_redir(char *str)
{
	int	i;
	int	redir;

	i = 0;
	redir = 0;
	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>')
			redir = i;
		if (str[i + 1] == redir)
		{
			i += 2;
			ft_printf("I'm in: %s\n", str + 1);
// 			while ()
		}
	}
	return (i);
}

//i[0] = word_pos
//i[1] = type
t_list	*fill_cmd_list(char *str)
{
	int		i;
	char	**pipes_list;
	t_list	*head;
	
	i = -1;
	pipes_list = ft_split(str, '|');
	if (!pipes_list)
		return (NULL);
	head = NULL;
	while (pipes_list[++i])
		ft_lstadd_back(&head, ft_lstnew(pipes_list[i], 0, i));
//	parse_special_chars(&head, '|');
	free (pipes_list);
	return (head);
}

//i[0] = quotes flag
//i[1] = in_word flag
//i[2] = count
t_list	*parser(char *str)
{
	t_list	*cmd;
	int		return_val;
//	int		*pos;
//	int		i[2];

	cmd = NULL;
	return_val = 0;
	ft_printf("\nGot input: %s\n", str);
	if (ft_strnstr(str, "||", ft_strlen(str)))
	{
		return_val = error_msg("minihell", "|", 2);
		return (NULL);
	}
	if (str[0] == '\\' && str[1])
		str = ft_remove_char(str, '\\');
	str = dquote(str);
	ft_printf("Final input: %s\n", str);
	cmd = fill_cmd_list(str);
	if (!cmd)
	{
		printf("Error");
		return (NULL);		
	}
//	pos = (int *)ft_calloc(3, sizeof(int));
/* 	while (str[i[0]])
	{
		get_args_pos(&str[i[0]], pos);
		if (pos[2])
			arg_list[i[1]++] = ft_substr(&str[i[0]], pos[0] + 1, pos[1] - 1);
		else
			arg_list[i[1]++] = ft_substr(&str[i[0]], pos[0], pos[1]);
		if (!arg_list[i[1] - 1])
			return (del_err_array(&arg_list, i[1] - 1));
		i[0] = i[0] + pos[0] + pos[1];
		if (pos[2])
			i[0]++;
	} */
	printf("%d\n", return_val);
	return (cmd);
}


/* int	main(int argc, char *argv[])
{
	t_list	*head;
	t_list	*node;
	char	*input;
	void	*tmp;

	printf("ac: %d\n", argc);
	if (argc > 1)
		input = ft_strdup(argv[1]);
	else
		return (0);
	printf("input: %s\n", input);
	head = parser(input);
	free(input);
	node = head;
	while (node)
	{
		ft_printf("Content: %s, type: %d, cmd_pos: %d\n", node->content, node->type, node->cmd_pos);
		free(node->content);
		tmp = node;
		node = node->next;
		free(tmp);
	}
	return (0);
} */

//cc -g src/parser.c -Ilib/libft -Iinclude -lreadline src/utils.c src/error_msgs.c lib/libft/libft.a
