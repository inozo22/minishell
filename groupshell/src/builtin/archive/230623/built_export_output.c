/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export_output.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 12:44:12 by nimai             #+#    #+#             */
/*   Updated: 2023/06/23 16:38:19 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @note Add '\' when the value string has '\' or '"'
 */
void	print_export(char	*str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\\' || str[i] == '"')
		{
			ft_putchar_fd('\\', 1);
		}
		ft_putchar_fd(str[i], 1);
		i++;
	}
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
				{
					ft_printf("=\"");
					print_export(list->box[i].val);
					ft_printf("\"");
				}
				ft_printf("\n");
			}
		}
		if (flag == FLAGENV && i == len - 1)
			break ;
	}
}

/**
 * @brief a part of initiation t_data
 * @author nimai
 * @param strs it's copy of envp
 * @note It's not beautiful to allocate 2000 each box[i].name and val, but it's necessary to sort.
 * i[0] = i
 * i[1] = len
 * i[2] = c
 */
t_export	*fill_list(char **env, t_export *ret)
{
	int			i[3];

	ft_bzero(i, 3 * sizeof(int));
	while (env[i[2]])
		i[2]++;
	while (i[0] < i[2])
	{
		ret->box[i[0]].equal = 0;
		ret->box[i[0]].id = i[0];
		i[1] = 0;
		while (env[i[0]][i[1]] != '=' && env[i[0]][i[1]] != '\0')
			i[1]++;
		if (env[i[0]][i[1]] == '=')
			ret->box[i[0]].equal = 1;
		ret->box[i[0]].name = ft_calloc(2000, sizeof(char));
		ret->box[i[0]].val = ft_calloc(2000, sizeof(char));
		if (!ret->box[i[0]].name || !ret->box[i[0]].val)
			return (NULL);
		ft_strlcpy(ret->box[i[0]].name, env[i[0]], i[1] + 1);
		ft_strlcpy(ret->box[i[0]].val, env[i[0]] + i[1] + 1, \
		ft_strlen(env[i[0]] + i[1]));
		i[0]++;
	}
	return (ret);
}

/* t_export	*fill_list(char **strs, t_export *ret)
{
	int			i[3];
	char		*tmp;

	ft_bzero(i, 3 * sizeof(int));
	while (strs[i[2]])
		i[2]++;
	ret->plen = i[2];
	while (i[0] < ret->plen)
	{
		ret->box[i[0]].equal = 0;
		ret->box[i[0]].id = i[0];
		if (!strs[i[0]])
			return (NULL);
		i[1] = 0;
		while (strs[i[0]][i[1]] != '=' && strs[i[0]][i[1]] != '\0')
			i[1]++;
		if (strs[i[0]][i[1]] == '=')
			ret->box[i[0]].equal = 1;
		ret->box[i[0]].name = ft_calloc(2000, sizeof(char));
		ret->box[i[0]].val = ft_calloc(2000, sizeof(char));
		if (!ret->box[i[0]].name || !ret->box[i[0]].val)
			return (NULL);
		ft_strlcpy(ret->box[i[0]].name, strs[i[0]], i[1] + 1);
		tmp = ft_substr(strs[i[0]], i[1] + 1, ft_strlen(strs[i[0]]) - i[1]);
		ft_strlcpy(ret->box[i[0]].val, tmp, ft_strlen(strs[i[0]]) - i[1] + 1);
		free (tmp);
		i[0]++;
	}
	return (ret);
} */

/**
 * @brief initiation t_data
 * @author nimai
 * @param name it will include until "="
 * @note It's not beautiful to allocate 2000 each box[i].name and val, but it's necessary to sort.
 * i[0] = i
 * i[1] = len
 * i[2] = c
 */
/* t_export	*fill_list(char **strs, t_export *ret)
{
	int			i[3];
	char		*tmp;

	ft_bzero(i, 3 * sizeof(int));
	while (strs[i[2]])
		i[2]++;
	ret->plen = i[2];
	while (i[0] < ret->plen)
	{
		ret->box[i[0]].equal = 0;
		ret->box[i[0]].id = i[0];
		if (!strs[i[0]])
			return (NULL);
		i[1] = 0;
		while (strs[i[0]][i[1]] != '=' && strs[i[0]][i[1]] != '\0')
			i[1]++;
		if (strs[i[0]][i[1]] == '=')
			ret->box[i[0]].equal = 1;
		ret->box[i[0]].name = ft_calloc(2000, sizeof(char));
		ret->box[i[0]].val = ft_calloc(2000, sizeof(char));
		if (!ret->box[i[0]].name || !ret->box[i[0]].val)
			return (NULL);
		ft_strlcpy(ret->box[i[0]].name, strs[i[0]], i[1] + 1);
		tmp = ft_substr(strs[i[0]], i[1] + 1, ft_strlen(strs[i[0]]) - i[1]);
		ft_strlcpy(ret->box[i[0]].val, tmp, ft_strlen(strs[i[0]]) - i[1] + 1);
		free (tmp);
		i[0]++;
	}
	return (ret);
} */

/**
 * @brief initiation t_data
 * @author nimai
 * @param name it will include until "="
 * @note It's not beautiful to allocate 2000 each box[i].name and val, but it's necessary to sort.
 */
/* t_export	*fill_list(char **strs, t_export *ret)
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
		ret->box[i].name = ft_calloc(2000, sizeof(char));
		ret->box[i].val = ft_calloc(2000, sizeof(char));
		if (!ret->box[i].name || !ret->box[i].val)
			return (NULL);
		ft_strlcpy(ret->box[i].name, strs[i], len + 1);
		tmp = ft_substr(strs[i], len + 1, ft_strlen(strs[i]) - len);
		ft_strlcpy(ret->box[i].val, tmp, ft_strlen(strs[i]) - len + 1);
		free (tmp);
	}
	return (ret);
} */

/**
 * @brief print export, until free t_export
 * @author nimai
 * @note I have taken from the built_export because of the amount of line
 */
int	output_export(t_data *data)
{
	char		**tmp_env;
	t_export	*list;
	int			i;

	tmp_env = data->env;
	list = NULL;
	if (!tmp_env)
		return (printf("Error: failure obtain env\n"), 0);
	list = (t_export *)ft_calloc(1, sizeof(t_export));
	if (!list)
		return (heap_error(1), 0);
	list = fill_list(tmp_env, list);
	if (!list)
		return (0);
	quick_sort(list->box, 0, av_amount(tmp_env) - 1);
	output_env(list, av_amount(tmp_env), FLAGEXPORT);
	i = 0;
	while (i < av_amount(tmp_env))
	{
		free (list->box[i].name);
		free (list->box[i].val);
		i++;
	}
	free (list);
	return (1);
}