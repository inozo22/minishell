/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:00:17 by nimai             #+#    #+#             */
/*   Updated: 2023/10/11 15:52:11 by nimai            ###   ########.fr       */
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
void	*envp_cd_mod(char ***env, char *path, int type)
{
	char	*tmp;

	tmp = NULL;
	if (!path)
		return (NULL);
	if (type == 1)
	{
		tmp = ft_calloc(ft_strlen(path) + 5, sizeof(char));
		if (!tmp)
			return (heap_error(1), NULL);
		ft_strcpy(tmp, "PWD=");
		ft_strcat(tmp, path);
	}
	else if (type == 2)
	{
		tmp = ft_calloc(ft_strlen(path) + 8, sizeof(char));
		if (!tmp)
			return (heap_error(1), NULL);
		ft_strcpy(tmp, "OLDPWD=");
		ft_strcat(tmp, path);
	}
	envp_strs_mod(tmp, env);
	free (tmp);
	return (NULL);
}

char	*str_mod(char *cur, char *str, int i, int len)
{
	int	j;

	j = 0;
	while (i < len && cur && cur[i])
	{
		cur[i] = str[j];
		i++;
		j++;
	}
	return (cur);
}

int	strcount(char *str1, char *str2, int len)
{
	int	ret;
	int	i;

	ret = 0;
	i = -1;
	while (ret < len && str1[++i])
	{
		if (ft_strcmp(&str1[i], str2) == 0)
			return (ret);
		ret++;
	}
	return (ret);
}

/**
 * @brief modifying path
 * @note get the whole path from cur, but change the string if it's input 
 * (cause should accept lower-case if it was)  
 */
char	*path_modify(char *cur, char *str)
{
	int		i;
	char	*tmp;

	if (ft_strlen(cur) > 1 && str[ft_strlen(str) - 1] == '/' \
	&& ft_strlen(cur) <= ft_strlen(str))
	{
		tmp = malloc(ft_strlen(cur) + 1);
		if (!tmp)
			return (NULL);
		ft_strlcpy(tmp, str, ft_strlen(cur) + 1);
		return (free (str), free (cur), tmp);
	}
	tmp = ft_strdup(str);
	ft_strlower(tmp);
	i = strcount(cur, tmp, ft_strlen(cur));
	cur = str_mod(cur, str, i, ft_strlen(cur));
	return (free (tmp), free (str), cur);
}
