/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:00:17 by nimai             #+#    #+#             */
/*   Updated: 2023/06/05 16:04:43 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief add environment according to dest in **
 * @author nimai
 * @return ** pointer, then free 
 * @note 230603nimai: Doesn't show PWD on Ubuntu (moji bake)
 */
void	envp_pwd_mod(t_temp *temp, char *dest)
{
	int		i;
	char	**tmp;
	int		x;

	i = 0;
	tmp = (char **)temp->envp;
	while (tmp[i])
	{
		if (ft_strncmp(tmp[i], "PWD", 3) == 0)
		{
			tmp[i] = NULL;
			tmp[i] = ft_strjoin("PWD=", dest);
			x = i;
		}
		i++;
	}
	temp->envp = tmp;
	free (tmp[x]);
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
	i = ft_strnstr_int(cur, tmp, ft_strlen(cur));
	cur = str_mod(cur, str, i);
	free (tmp);
	return (cur);
}