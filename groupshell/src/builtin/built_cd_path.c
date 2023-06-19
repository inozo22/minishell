/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:00:17 by nimai             #+#    #+#             */
/*   Updated: 2023/06/19 17:36:56 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief add environment according to dest in **
 * @author nimai
 * @param type 1 is PWD, 2 is OLDPWD
 * @param path could be currently path or destination path
 * @return ** pointer, then free 
 * @note 230603nimai: Doesn't show PWD on Ubuntu (moji bake)
 */
t_data	*envp_cd_mod(t_data *data, char *path, int type)
{
	char	*tmp;

	tmp = NULL;
	if (!path)
		return (data);
	else if (type == 1)
	{
		tmp = ft_calloc(ft_strlen(path) + 5, sizeof(char));
		if (!tmp)
			return (heap_error(1), NULL);
		ft_strlcpy(tmp, "PWD=", 5);
		ft_strcat(tmp, path);
	}
	else if (type == 2)
	{
		tmp = ft_calloc(ft_strlen(path) + 8, sizeof(char));
		if (!tmp)
			return (heap_error(1), NULL);
		ft_strlcpy(tmp, "OLDPWD=", 8);
		ft_strcat(tmp, path);
	}
	envp_strs_mod(tmp, data);
	free (tmp);
	return (data);
}

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

char	*str_mod(char *cur, char *str, int i)
{
	int	j;

	j = 0;
	while (cur[i])
	{
		cur[i] = str[j];
		i++;
		j++;
	}
	return (cur);
}

/**
 * @brief modifying path
 * @author nimai
 * @note get the whole path from cur, but change the string if it's input (cause should accept lower-case if it was)  
 */
char	*path_modify(char *cur, char *str)
{
	int		i;
	char	*tmp;

	tmp = malloc(ft_strlen(str) + 1);
	ft_strlcpy(tmp, str, ft_strlen(str) + 1);
	ft_strlower(tmp);
	i = ft_strnstr(cur, tmp, ft_strlen(cur)) - cur;
	cur = str_mod(cur, str, i);
	free (tmp);
	return (cur);
}
