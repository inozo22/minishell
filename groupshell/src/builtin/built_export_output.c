/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export_output.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 12:44:12 by nimai             #+#    #+#             */
/*   Updated: 2023/06/19 18:29:56 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief check oldpwd and if not add
 * @author nimai
 * @param 
 * @note if there is no "OLDPWD", add without value
 */
/* void	check_oldpwd(t_data *data)
{
	int			i;
	char		**new_envp;

	new_envp = NULL;
	i = -1;
	while (data->env[++i])
	{
		if (ft_strncmp(data->env[i], "OLDPWD", 6) == 0)
			return ;
	}
	new_envp = envp_strs_join("OLDPWD", data);
	if (!new_envp)
		return ;
	data->env = new_envp;
} */

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
	int			c;

	c = 0;
	while (strs[c])
		c++;
	ret->plen = c;
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
		ret->box[i].name = ft_calloc(1, 2000);
		ret->box[i].val = ft_calloc(1, 2000);
		if (!ret->box[i].name || !ret->box[i].val)
			return (NULL);
		ft_strlcpy(ret->box[i].name, strs[i], len + 1);
		tmp = ft_substr(strs[i], len + 1, ft_strlen(strs[i]) - len);
		ft_strlcpy(ret->box[i].val, tmp, ft_strlen(strs[i]) - len + 1);
		free (tmp);
	}
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

//	check_oldpwd(data);
	tmp_env = data->env;
	list = NULL;
	if (!tmp_env)
		return (printf("Error: failure obtain env\n"), 0);
	list = (t_export *)ft_calloc(1, sizeof(t_export));
	if (!list)
		return (heap_error(1), 0);
	list = fill_list(tmp_env, list);
	quick_sort(list->box, 0, av_amount(tmp_env) - 1);
	output_env(list, av_amount(tmp_env), FLAGEXPORT);
	int i = 0;
	while (i < av_amount(tmp_env))
	{
		free (list->box[i].name);
		free (list->box[i].val);
		i++;
	}
	free (list);
	return (1);
}
