/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 09:50:35 by nimai             #+#    #+#             */
/*   Updated: 2023/06/15 11:33:18 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief manage "builtin" unset cmd.
 * @author nimai
 * @param **av "unset", "ABC", "DEF"
 * @note how to delete a variable??? 
 */
t_data	*unset_env(t_data *data, char *str)
{
	int		i;
	int		j;
	char	**tmp;

	i = -1;
	j = -1;
	tmp = (char **)malloc(sizeof(char *) * (av_amount(data->env) + 1));
	if (!tmp)
		return (NULL);
	while (data->env[++i])
	{
		if (ft_strncmp(data->env[i], str, ft_strlen(str)) || \
		ft_strncmp(str, data->env[i], ft_strlen(str)))
		{
			tmp[++j] = data->env[i];
		}
		data->env[i] = NULL;
	}
	free (data->env);
	data->env = tmp;
	return (data);
}

/**
 * @brief manage "builtin" unset cmd.
 * @author nimai
 * @param **av "unset", "ABC", "DEF"
 * @note if it's not valid, receive error message, but if it's valid and doesn't exist will not receive anything
 */
int	built_unset(char **input, t_data *data)
{
	int		i;

	i = 1;
	while (input[i])
	{
		if (check_valid(input[i], "unset") == 1)
			data = unset_env(data, input[i]);
		i++;
	}
	return (0);
}

/**
 * BEHAVIOUR IN BASH
 * when execute env, the list is not ordered 
 * 
 * 
 * 
 * 230601nimai: 
 * unset: kind of did it, but should be started over after it've been decided on the structure."
[main b02d1eb] unset: kind of did it, but should be started over after it've been decided on the structure
 * 230615nimai: done.
 * 
 */
