/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export_output.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 12:44:12 by nimai             #+#    #+#             */
/*   Updated: 2023/10/10 11:42:32 by nimai            ###   ########.fr       */
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
			ft_printf("\"");
		}
		else
			ft_printf("%s", list->content);
		ft_printf("\n");
		list = list->next;
	}
}

void	sort_list(t_list *list)
{
	int		len;
	t_list	*head;
	char	*tmp;

	head = list;
	while (list->next)
	{
		len = ft_strchr(list->content, '=') - list->content;
		if (len < ft_strchr(list->next->content, '=') - list->next->content)
			len = ft_strchr(list->next->content, '=') - list->next->content;
		if (ft_strncmp(list->content, list->next->content, len) > 0)
		{
			tmp = list->content;
			list->content = list->next->content;
			list->next->content = tmp;
			list = head;
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
