/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:52:54 by nimai             #+#    #+#             */
/*   Updated: 2023/06/21 12:05:50 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief string checker for variable.
 * @author nimai
 * @return 1 if it's valid, otherwise 0.
 * @note in built_utils.
 * @note builtin global function
 */
int	check_valid(char *str, char *cmd, t_data *data)
{
	int	i;

	i = 0;
	if (!(ft_isalpha(str[i]) || str[i] == '_'))
	{
		data->return_val = 1;
		return (error_id_built(cmd, str, "not a valid identifier"), 0);
	}
	i++;
	while (str[i] != '=' && str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_' && (str[i] != '=' && \
		ft_strncmp(cmd, "export", 6) == 0))
		{
			data->return_val = 1;
			return (error_id_built(cmd, str, "not a valid identifier"), 0);
		}
		i++;
	}
	return (1);
}

/**
 * @brief get_env, get value of env
 * @author nimai
 * @param
 * @return 
 * @note if there is no value (or variable) return NULL
 */
char	*get_env(char **env, char *type)
{
	int		i;
	int		j;

	i = -1;
	while (env[++i])
	{
		j = 0;
		while (env[i][j] && type[j] && env[i][j] == type[j])
			j++;
		if (env[i][j] == '=' && type[j] == '\0')
			break ;
	}
	if (env[i] && ft_strrchr(env[i], '='))
		return (ft_strdup(env[i] + ft_strlen(type) + 1));
	else
		return (NULL);//not set error coco?
}