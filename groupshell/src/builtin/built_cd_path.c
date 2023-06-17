/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:00:17 by nimai             #+#    #+#             */
/*   Updated: 2023/06/17 11:08:19 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief add environment according to dest in **
 * @author nimai
 * @param path 1 is PWD, 2 is OLDPWD
 * @return ** pointer, then free 
 * @note 230603nimai: Doesn't show PWD on Ubuntu (moji bake)
 */
t_data	*envp_cd_mod(t_data *data, char *dest, int path)
{
	char	*str;

	str = NULL;
	if (path == 1)
	{
		str = ft_calloc(ft_strlen(dest) + 5, sizeof(char));
		if (!str)
			return (NULL);
		ft_strlcpy(str, "PWD=", 5);
		ft_strcat(str, dest);
	}
	else if (path == 2)
	{
		str = ft_calloc(ft_strlen(dest) + 8, sizeof(char));
		if (!str)
			return (NULL);
		ft_strlcpy(str, "OLDPWD=", 8);
		ft_strcat(str, dest);
	}
	envp_strs_mod(str, data);
	free (str);
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
