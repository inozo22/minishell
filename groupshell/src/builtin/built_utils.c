/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:52:54 by nimai             #+#    #+#             */
/*   Updated: 2023/06/15 17:30:40 by nimai            ###   ########.fr       */
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
int	check_valid(char *str, char *cmd)
{
	int	i;

	i = 0;
	if (!(ft_isalpha(str[i]) || str[i] == '_'))
	{
		error_av_built(cmd, str, "not a valid identifier");
		return (0);
	}
	i++;
	while (str[i] != '=' && str[i])
	{
		if (ft_isalnum(str[i]) || str[i] == '_' || (str[i] == '=' && \
		ft_strncmp(cmd, "export", 6) == 0))
			;
		else
		{
			error_av_built(cmd, str, "not a valid identifier");
			return (0);
		}
		i++;
	}
	if (str[i] == '=')
	{
		while (str[i])
		{
			if (ft_isprint(str[i]))
				;
			else
			{
				error_av_built(cmd, str, "not a valid identifier");
				return (0);
			}
			i++;
		}
	}
	return (1);
}

/**
 * @brief get_env, especially it's for 
 * @author nimai
 * @param **av "cd", "path".
 * @return 
 * @note 
 */
char	*get_env(char **env, char *type)
{
//	char	*ret;
	int		i;

	i = -1;
	while (env[++i])
		if (ft_strnstr(env[i], type, ft_strlen(type)))
			break ;
	if (env[i] && ft_strrchr(env[i], '='))
		return (ft_strdup(env[i] + ft_strlen(type) + 1));
	else
		return (NULL);//not set coco?
}

