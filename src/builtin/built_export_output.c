/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export_output.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 12:44:12 by nimai             #+#    #+#             */
/*   Updated: 2023/12/08 13:53:22 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_value(char *str)
{
	int	i;

	i = 0;
	if (ft_strchr(str, '"') || ft_strchr(str, '$') || \
	ft_strchr(str, '`') || ft_strchr(str, '\\'))
	{
		while (str[i])
		{
			if (str[i] == '\"' || str[i] == '$' || \
			str[i] == '`' || str[i] == '\\')
				ft_printf("%c", '\\');
			ft_printf("%c", str[i]);
			i++;
		}
	}
	else
		ft_printf("%s", str);
}

/**
 * @brief output all list
 * @author nimai
 * @param flag control between env and export (230526)
 * @note maybe adjust to some list too.
 * @note 230905bde-mada: added condition to skip '_' variable
 * @note 230912nimai: removed flags and fixed condition to skip '_' variable
 * @note 231010nimai: remake this function to accept any size of string
 */
void	output_env(t_export *list)
{
	int		len;

	while (list)
	{
		if (ft_strncmp(list->content, "_=", 2) == 0)
		{
			list = list->next;
			continue ;
		}
		write(1, "declare -x ", 11);
		if (ft_strchr(list->content, '='))
		{
			len = ft_strchr(list->content, '=') - list->content;
			write(1, list->content, len);
			write(1, "=\"", 2);
			print_value(list->content + len + 1);
			write(1, "\"\n", 2);
		}
		else
			ft_printf("%s\n", list->content);
		list = list->next;
	}
}

/**
 * @note ft_strcmp without value, strncmp with value
 */
void	sort_list(t_export *list)
{
	t_export	*head;
	char		*tmp_content;
	char		*tmp_name;

	head = list;
	while (list && list->next)
	{
		if (ft_strcmp(list->name, list->next->name) > 0)
		{
			tmp_content = list->content;
			tmp_name = list->name;
			list->content = list->next->content;
			list->name = list->next->name;
			list->next->content = tmp_content;
			list->next->name = tmp_name;
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
t_export	*fill_list(char **env, t_export *list)
{
	int			amount;
	int			i;
	t_export	*next;
	t_export	*head;

	i = 0;
	list = new_export(ft_strdup(env[i]), ft_substr(env[i], 0, \
	ft_strchr(env[i], 61) - env[i]));
	if (!list)
		return (heap_error(1), NULL);
	head = list;
	amount = av_amount(env);
	while (++i < amount)
	{
		if (ft_strchr(env[i], 61))
			next = new_export(ft_strdup(env[i]), ft_substr(env[i], 0, \
			ft_strchr(env[i], 61) - env[i]));
		else
			next = new_export(ft_strdup(env[i]), ft_strdup(env[i]));
		export_add_back(&list, next);
	}
	return (head);
}

/**
 * @brief print export, then free t_export
 * @author nimai
 * @note 231010nimai: remake to accept any size of string
 */
int	output_export(char **env)
{
	char		**tmp_env;
	t_export	*list;

	tmp_env = env;
	list = NULL;
	if (!tmp_env)
		return (ft_printf("Error: failure obtain env\n"), 0);
	list = fill_list(tmp_env, list);
	if (!list)
		return (0);
	sort_list(list);
	output_env(list);
	export_clear(&list, free);
	return (1);
}
