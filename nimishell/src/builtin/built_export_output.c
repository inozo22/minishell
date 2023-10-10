/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export_output.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 12:44:12 by nimai             #+#    #+#             */
/*   Updated: 2023/10/10 16:04:27 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief output all list
 * @author nimai
 * @param flag control between env and export (230526)
 * @note maybe adjust to some list too.
 * @note 230905bde-mada: added condition to skip '_' variable
 * @note 230912nimai: removed flags and fixed condition to skip '_' variable
 * @note 231010nimai: remake this function to accept any size of string
 */
void	output_env(t_list *list)
{
	int		len;

	while (list)
	{
		if (ft_strncmp(list->content, "_=", 2) == 0)
		{
			list = list->next;
			continue ;
		}
		ft_printf("declare -x ");
		if (ft_strchr(list->content, '='))
		{
			len = ft_strchr(list->content, '=') - list->content;
			write(1, list->content, len);
			ft_printf("=\"");
			ft_printf(list->content + len + 1);
			ft_printf("\"\n");
		}
		else
			ft_printf("%s\n", list->content);
		list = list->next;
	}
}

// void	sort_list(t_list *list)
// {
// 	int		len;
// 	t_list	*head;
// 	char	*tmp;

// 	head = list;
// 	while (list && list->next)
// 	{
// 		if (ft_strchr(list->content, 61) && ft_strchr(list->next->content, 61))
// 		{
// 			len = ft_strchr(list->content, 61) - list->content;
// 			if (len > ft_strchr(list->next->content, 61) - list->next->content)
// 				len = ft_strchr(list->next->content, 61) - list->next->content;
// 		}
// 		else if (ft_strchr(list->content, 61))
// 			len = ft_strchr(list->content, 61) - list->content;
// 		else if (ft_strchr(list->next->content, 61))
// 			len = ft_strchr(list->next->content, 61) - list->next->content;
// 		else
// 			len = -1;
// 		if ((len == -1 && ft_strcmp(list->content, list->next->content) > 0) || (len && ft_strncmp(list->content, list->next->content, len) > 0))
// 		{
// 			tmp = list->content;
// 			list->content = list->next->content;
// 			list->next->content = tmp;
// 			list = head;
// 			continue ;
// 		}
// 		list = list->next;
// 	}
// }

void	sort_list(t_list *list)
{
	int		len;
	int		len1;
	int		len2;
	t_list	*head;

	head = list;
	while (list && list->next)
	{
		len1 = ft_strchr(list->content, 61) - list->content;
		len2 = ft_strchr(list->next->content, 61) - list->next->content;
		len = check_variable_len(len1, len2);
		if ((len == -1 && ft_strcmp(list->content, list->next->content) > 0) || \
		(len && ft_strncmp(list->content, list->next->content, len) > 0))
		{
			swap_list(&list, head);
			continue ;
		}
		list = list->next;
	}
}

/**
 * @author nimai
 * @note confirmed that there is no memory leaks
 */
t_list	*fill_list(char **env, t_list *list)
{
	int		amount;
	int		i;
	t_list	*next;
	t_list	*head;

	i = 0;
	list = ft_lstnew(ft_strdup(env[i]), 0, 0);
	if (!list)
		return (heap_error(1), NULL);
	head = list;
	amount = av_amount(env);
	while (++i < amount)
	{
		next = ft_lstnew(ft_strdup(env[i]), 0, 0);
		ft_lstadd_back(&list, next);
	}
	return (head);
}

/**
 * @brief print export, then free t_list
 * @author nimai
 * @note 231010nimai: remake to accept any size of string
 */
int	output_export(t_data *data)
{
	char		**tmp_env;
	t_list		*list;

	tmp_env = data->env;
	list = NULL;
	if (!tmp_env)
		return (printf("Error: failure obtain env\n"), 0);
	list = fill_list(tmp_env, list);
	if (!list)
		return (0);
	sort_list(list);
	output_env(list);
	ft_lstclear(&list, free);
	return (1);
}
