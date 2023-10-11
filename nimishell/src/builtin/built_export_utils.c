/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 14:25:44 by nimai             #+#    #+#             */
/*   Updated: 2023/10/11 17:49:44 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_export	*new_export(char *content, char *name)
{
	t_export	*new;

	new = (t_export *)malloc(sizeof(t_export));
	if (!new)
		return (NULL);
	new->content = content;
	new->name = name;
	new->next = NULL;
	return (new);
}

void	export_add_back(t_export **list, t_export *newnode)
{
	t_export	*start;

	start = *list;
	if (*list)
	{
		while (start->next)
			start = start->next;
		start->next = newnode;
	}
	else
		*list = newnode;
}

void	*export_clear(t_export **list, void (*del)(void *))
{
	if (list && *list)
	{
		export_clear(&(*list)->next, del);
		if (*list)
		{
			del((*list)->content);
			del((*list)->name);
			free (*list);
		}
		*list = NULL;
	}
	return (NULL);
}

/**
 * 
 * @param flag if there is no '=', you will put one more length to
 * allocate memory
 */
char	*envp_str_mod(char *str, char *input, int i, int flag)
{
	free (str);
	str = ft_calloc(ft_strlen(input) + 1 + flag, sizeof(char));
	if (!str)
	{
		return (NULL);
	}
	ft_strlcpy(str, input, i + 2);
	ft_strcat(str, (input + i + 1));
	return (str);
}

int	check_input(char *input, char **env)
{
	int	c;
	int	i;
	int	j;

	i = 0;
	while (env[i])
	{
		c = 0;
		j = -1;
		while (env[i][++j] == input[c] && input[c] != '=' \
		&& input[c] != '\0' && env[i][j])
			c++;
		if ((input[c] == '=' && env[i][j] == '\0') || (env[i][j] \
		== '=' && input[c] == '\0') || (env[i][j] == input[c]))
			return (c);
		i++;
	}
	return (0);
}
