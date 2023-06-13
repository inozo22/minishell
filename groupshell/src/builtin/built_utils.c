/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:52:54 by nimai             #+#    #+#             */
/*   Updated: 2023/06/13 11:54:18 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built.h"

static char	*get_env(char **env, char *type)
{
	int	i;

	i = -1;
	while (env[++i])
		if (ft_strnstr(env[i], type, ft_strlen(type)))
			break ;
	if (env[i])
		return (ft_strdup(env[i] + ft_strlen(type)));
	else
		return (NULL);
}
