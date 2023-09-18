/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:52:54 by nimai             #+#    #+#             */
/*   Updated: 2023/09/18 11:41:10 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @note it's not so cool, but can I use it?
 * @note check_valid is a test case
 */
void	set_return(int val)
{
	g_return_val = val;
}

/**
 * @brief string checker for variable.
 * @author nimai
 * @return 1 if it's valid, otherwise 0.
 * @note in built_utils.
 */
int	check_valid(char *str, char *cmd)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		return (set_return(2), error_id_built(cmd, str, "invalid option"), 0);
	if (!(ft_isalpha(str[i]) || str[i] == '_'))
		return (set_return(1), \
		error_id_built(cmd, str, "not a valid identifier"), 0);
	i++;
	while (str[i] != '=' && str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_' && (str[i] != '=' && \
		ft_strncmp(cmd, "export", 6) == 0))
			return (set_return(1), \
			error_id_built(cmd, str, "not a valid identifier"), 0);
		i++;
	}
	g_return_val = 0;
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
		return (NULL);//error msg
}

/**
 * @note this function is used in check_builtin too, maybe change the file
  */
char	*ft_strlower(char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = str;
	while (tmp[i])
	{
		tmp[i] = ft_tolower(str[i]);
		i++;
	}
	return (tmp);
}
