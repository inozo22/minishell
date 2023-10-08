/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export_output.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 12:44:12 by nimai             #+#    #+#             */
/*   Updated: 2023/10/08 18:23:45 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @note Add '\' when the value string has '\' or '"'
 * @note 230915nimai: add slash also there is '$'
 */
// void	print_export(char	*str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '\\' || str[i] == '"' || str[i] == '$')
// 		{
// 			ft_putchar_fd('\\', 1);
// 		}
// 		ft_putchar_fd(str[i], 1);
// 		i++;
// 	}
// }

/**
 * @brief output all list
 * @author nimai
 * @param flag control between env and export (230526)
 * @note maybe adjust to some list too.
 * @note 230905bde-mada: added condition to skip '_' variable
 * @note 230912nimai: removed flags and fixed condition to skip '_' variable
 */
void	output_env(t_list *list)
{
	// t_list	*head;
	int		len;

	// list = head;
	while (list)
	{
		if (ft_strncmp(list->content, "_=", 2) == 0)
		{
			list = list->next;
			continue ;
		}
		if (ft_strchr(list->content, '='))
		{
			len = ft_strchr(list->content, '=') - list->content;
			printf("len: %d\n", len);
			ft_printf("declare -x ");
			write(1, list->content, len);
			ft_printf("=\"");
			ft_printf(list->content + len + 1);
			ft_printf("\"");
		}
		else
		{
			ft_printf("declare -x ");
			ft_printf("%s", list->content);
			ft_printf("\n");
		}
		list = list->next;
	}

	// j = -1;
	// while (++j < len)
	// {
	// 	i = -1;
	// 	while (++i < len)
	// 	{
	// 		if (list->box[i].id == j && ft_strcmp(list->box[i].name, "_") != 0)
	// 		{
	// 			ft_printf("declare -x ");
	// 			ft_printf("%s", list->box[i].name);
	// 			if (list->box[i].equal == 1)
	// 			{
	// 				ft_printf("=\"");
	// 				print_export(list->box[i].val);
	// 				ft_printf("\"");
	// 			}
	// 			ft_printf("\n");
	// 		}
	// 	}
	// }
}

/**
 * @brief a part of initiation t_data
 * @author nimai
 * @param strs it's copy of envp
 * @note It's not beautiful to allocate 2000 each box[i].name and val,
 * but it's necessary to sort.
 * i[0] = i
 * i[1] = len
 * i[2] = c
 */
t_list	*fill_list(char **env, t_list *list)
{
	int		amount;
	int		i;
	t_list	*next;
	t_list	*head;

	i = 0;
	list = ft_lstnew(ft_strdup(env[i]), 0, 0);
	printf("env[%d]: %s\n", i, env[i]);
	if (!list)
		return (heap_error(1), NULL);
	head = list;
	amount = av_amount(env);
	while (++i < amount)
	{
		next = ft_lstnew(ft_strdup(env[i]), 0, 0);
		ft_lstadd_back(&list, next);
		printf("env[%d]: %s\n", i, env[i]);
	}
	return (head);
}

/**
 * @brief print export, then free t_export
 * @author nimai
 */
int	output_export(t_data *data)
{
	char		**tmp_env;
	t_list		*list;
	int			i;

	tmp_env = data->env;
	list = NULL;
	if (!tmp_env)
		return (printf("Error: failure obtain env\n"), 0);
	list = fill_list(tmp_env, list);
	if (!list)
		return (0);
	sort_list(list);
	output_env(list/* , av_amount(tmp_env) */);
	printf("Hello! Im here!\n");
	i = 0;
	while (i < av_amount(tmp_env))
	{
		i++;
	}
	free (list);
	return (1);
}
