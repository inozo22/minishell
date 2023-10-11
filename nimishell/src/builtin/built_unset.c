/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 09:50:35 by nimai             #+#    #+#             */
/*   Updated: 2023/10/11 13:28:40 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief manage "builtin" unset cmd.
 * @author nimai
 * @param **av "unset", "ABC", "DEF"
 */
void	*unset_env(char ***env, char *str)
{
	int		i;
	int		j;
	int		len;
	char	**tmp;

	i = -1;
	j = -1;
	tmp = (char **)malloc(sizeof(char *) * (av_amount(*env) + 1));
	if (!tmp)
		return (heap_error(1), NULL);
	len = ft_strlen(str);
	while ((*env)[++i])
	{
		if (ft_strnstr((*env)[i], str, len) && ((*env)[i][len] == '=' || \
		(*env)[i][len] == '\0'))
			;
		else
			tmp[++j] = ft_strdup((*env)[i]);
		free ((*env)[i]);
		(*env)[i] = NULL;
	}
	tmp[++j] = NULL;
	free (*env);
	*env = tmp;
	return (NULL);
}

/**
 * @brief manage "builtin" unset cmd.
 * @author nimai
 * @param **av "unset", "ABC", "DEF"
 * @note if it's not valid, receive error message, but if it's valid and doesn't
 *  exist will not receive anything
 * @note unset not unset _???
 */
int	built_unset(char **input, char ***env)
{
	int		i;
	int		len;

	i = 1;
	len = av_amount(input);
	while (i < len)
	{
		if (check_valid(input[i], "unset") == 1)
		{
			unset_env(env, input[i]);
		}
		i++;
	}
	return (0);
}
