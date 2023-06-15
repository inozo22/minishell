/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export_output.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 12:44:12 by nimai             #+#    #+#             */
/*   Updated: 2023/06/15 12:04:39 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief check oldpwd and if not add
 * @author nimai
 * @param 
 * @note if there is no "OLDPWD", add without value
 */
void	check_oldpwd(t_data *data)
{
	int			i;
	char		**new_envp;

	new_envp = NULL;
	i = -1;
	while (data->env[++i])
	{
		if (ft_strncmp(data->env[i], "OLDPWD=", 7) == 0 || ft_strncmp(data->env[i], "OLDPWD", 6) == 0)
			return ;
	}
	new_envp = envp_strs_join("OLDPWD", data);
	if (!new_envp)
		return ;
	data->env = new_envp;
//	strs_free(new_envp);
}

/**
 * @brief output all list
 * @author nimai
 * @param flag control between env and export (230526)
 * @note maybe adjust to some list too.
 */
void	output_env(t_export *list, int len, int flag)
{
	int	i;
	int	j;

	j = -1;
	while (++j < len)
	{
		i = -1;
		while (++i < len)
		{
			if (list->box[i].id == j && flag == FLAGEXPORT)
			{
				ft_printf("declare -x ");
				ft_printf("%s", list->box[i].name);
				if (list->box[i].equal == 1)
					ft_printf("=\"%s\"", list->box[i].val);
				ft_printf("\n");
			}
		}
		if (flag == FLAGENV && i == len - 1)
			break ;
	}
}

/**
 * @brief initiation t_data
 * @author nimai
 * @param name it will include until "="
 * @note It's not beautiful to allocate 2000 each box[i].name and val, but it's necessary to sort.
 */
t_export	*fill_list(char **strs, t_export *ret)
{
	int			i;
	int			len;
	char		*tmp;

	printf("Line: %d\n", __LINE__);
	ret->plen = av_amount(strs);
	i = -1;
	while (++i < ret->plen)
	{
		ret->box[i].equal = 0;
		ret->box[i].id = i;
		if (!strs[i])
			return (NULL);
		len = 0;
		while (strs[i][len] != '=' && strs[i][len] != '\0')
			len++;
		if (strs[i][len] == '=')
			ret->box[i].equal = 1;
		printf("Line: %d ret->box[%d].equal: %d\n", __LINE__, i, ret->box[i].equal);
		ret->box[i].name = ft_calloc(1, 2000);
		ret->box[i].val = ft_calloc(1, 2000);
		if (!ret->box[i].name || !ret->box[i].val)
			return (NULL);
		ft_strlcpy(ret->box[i].name, strs[i], len + 1);
		printf("ret->box[%d].name: %s\n", i, ret->box[i].name);
		tmp = ft_substr(strs[i], len + 1, ft_strlen(strs[i]) - len);
		ft_strlcpy(ret->box[i].val, tmp, ft_strlen(strs[i]) - len + 1);
		printf("ret->box[%d].val: %s\n", i, ret->box[i].val);
		free (tmp);
	}
	printf("Line: %d\n", __LINE__);
	return (ret);
}

/**
 * @brief print export, until free t_export
 * @author nimai
 * @note I have taken from the built_export because of the amount of line
 */
int	output_export(t_data *data)
{
	char		**tmp_env;
	t_export	*list;

	check_oldpwd(data);
	tmp_env = data->env;
	list = NULL;
	if (!tmp_env)
		return (printf("Error: failure obtain env\n"), 0);
	list = (t_export *)malloc(sizeof(t_export));
	if (!list)
		return (heap_error(1), 0);
	list = fill_list(tmp_env, list);
	printf("Line: %d\n", __LINE__);
	quick_sort(list->box, 0, av_amount(tmp_env) - 1);
	printf("Line: %d\n", __LINE__);
	output_env(list, av_amount(tmp_env), FLAGEXPORT);
//	free (list);
	return (1);
}