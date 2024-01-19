/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:52:54 by nimai             #+#    #+#             */
/*   Updated: 2023/12/11 13:41:27 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief to know argv's amount.
 * @author nimai
 * @return how many argvs you have, in int. 
 */
int	av_amount(char **strs)
{
	int	ret;

	ret = 0;
	while (strs && strs[ret])
	{
		ret++;
	}
	return (ret);
}

/**
 * @note it's not so cool, but can I use it?
 * @note check_valid is a test case
 */
void	set_return(int val, t_data *data)
{
	data->return_val = val;
}

/**
 * @brief string checker for variable.
 * @author nimai
 * @return 1 if it's valid, otherwise 0.
 * @note in built_utils.
 * @note 231011nimai: add condition to check to ignore '_' with unset
 */
int	check_valid(char *str, char *cmd, t_data *data)
{
	int		i;
	char	tmp[3];

	i = 0;
	if (!ft_strcmp(cmd, "unset") && !ft_strcmp(str, "_"))
		return (0);
	if (str[i] == '-' && str[i + 1])
	{
		ft_strlcpy(tmp, str, 3);
		return (data->return_val = 2, error_av_built(cmd, tmp, \
		"invalid option"), 0);
	}
	if (!(ft_isalpha(str[i]) || str[i] == '_'))
		return (data->return_val = 1, \
	error_id_built(cmd, str, "not a valid identifier"), 0);//231214nimai:remove free after error message
	while (str[++i] != '=' && str[i])
	{
		if ((!ft_isalnum(str[i]) && str[i] != '_') || \
		(str[i + 1] && str[i + 1] == '=' && !ft_strcmp(cmd, "unset")))
			return (data->return_val = 1, \
			error_id_built(cmd, str, "not a valid identifier"), free(str), 0);
	}
	data->return_val = 0;
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
		return (NULL);
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
