/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:00:17 by nimai             #+#    #+#             */
/*   Updated: 2023/09/07 19:58:28 by nimai            ###   ########.fr       */
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
	envp_strs_mod(tmp, data);
	free (tmp);
	return (data);
}

// /**
//  * @note this function is used in check_builtin too, maybe change the file
//   */
// char	*ft_strlower(char *str)
// {
// 	int		i;
// 	char	*tmp;

// 	i = 0;
// 	tmp = str;
// 	while (tmp[i])
// 	{
// 		tmp[i] = ft_tolower(str[i]);
// 		i++;
// 	}
// 	return (tmp);
// }

char	*str_mod(char *cur, char *str, int i, int len)
{
	int	j;

	j = 0;
	printf("%scur: %s len: %d%s\n", COLOR_YELLOW, cur, len, COLOR_RESET);
	while (i < len && cur && cur[i])
	{
		printf("cur: %s i: %d%s\n", cur, i, COLOR_RESET);
		cur[i] = str[j];
		i++;
		j++;
	}
	return (cur);
}

int	strcount(char *str1, char *str2, int len)
{
	int	ret;

	ret = 0;
	while (ret < len && ft_strcmp(str1, str2))
	{
		str1++;
		str2++;
		ret++;
	}
	return (ret);
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

	// tmp = malloc(ft_strlen(str) + 1);
	// if (!tmp)
	// 	return (NULL);//error memory allocation
	// ft_strlcpy(tmp, str, ft_strlen(str) + 1);
	if (!cur)
	{
		tmp = malloc(ft_strlen(str));
		if (!tmp)
			return (NULL);//error memory allocation
		ft_strlcpy(tmp, str, ft_strlen(str));
		return (tmp);
	}
	tmp = ft_strdup(str);
	ft_strlower(tmp);
	i = strcount(cur, tmp, ft_strlen(cur));
//	i = ft_strnstr(cur, tmp, ft_strlen(cur)) - cur;
	printf("%sLINE: %d	cur: %s i: %d%s\n", COLOR_YELLOW, __LINE__, cur, i, COLOR_YELLOW);
	cur = str_mod(cur, str, i, ft_strlen(cur));
	free (tmp);
	return (cur);
}
