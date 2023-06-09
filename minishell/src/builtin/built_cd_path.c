/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-mada <bde-mada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:00:17 by nimai             #+#    #+#             */
/*   Updated: 2023/06/08 18:11:45 by bde-mada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief add environment according to dest in **
 * @author nimai
 * @return ** pointer, then free 
 * @note 230603nimai: Doesn't show PWD on Ubuntu (moji bake)
 */
t_data	*envp_pwd_mod(t_data *data, char *dest)
{
	int		i;
	char	*str;
	int		x;

	str = NULL;
	i = 0;
	ft_printf("DEST: %s\n", dest);
	while (data->env[i])
	{
		if (ft_strcmp(data->env[i], "PWD") == 0)
		{
			data->env[i] = NULL;
			printf("Line: %d	tmp[%d]: %s\n", __LINE__, i, data->env[i]);
			str = ft_strjoin("PWD=", dest);
			data->env[i] = str;
			printf("Line: %d	tmp[%d]: %s\n", __LINE__, i, data->env[i]);
			x = i;
		}
		i++;
	}
	free (str);
//	free (tmp[x]);
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
