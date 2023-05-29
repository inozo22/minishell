/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 10:18:56 by nimai             #+#    #+#             */
/*   Updated: 2023/05/29 11:06:49 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
				ft_printf("\"%s\"\n", list->box[i].val);
			}
		}
		if (flag == FLAGENV && i == len - 1)
			break ;
	}

}

/**
 * @brief temporary error management
 * @author nimai
 * @note when decided error management, merge it.
 */
void	error_export(char *cmd)
{
	ft_printf("minishell: export: %s: Dunno\n", cmd);
}

t_export	*fill_list(char **strs, t_export *ret)
{
	int			i;
	int			len;
	char		*tmp;

	ret->plen = av_amount(strs);
	i = -1;
	while (++i < ret->plen)
	{
		ret->box[i].id = i;
		if (!strs[i])
			return (NULL);
		len = 0;
		while (strs[i][len] != '=')/* strs[i][len] &&  */
			len++;
		ret->box[i].name = malloc(2000);
		ft_strlcpy(ret->box[i].name, strs[i], len + 2);//230525nimai: included until '='
		tmp = ft_substr(strs[i], len + 1, ft_strlen(strs[i]) - len);
		ret->box[i].val = malloc(2000);
		ft_strlcpy(ret->box[i].val, tmp, ft_strlen(strs[i]) - len + 1);
	}
	return (ret);
}



/**
 * @brief check if the path exists.
 * @author nimai
 * @note 
 */
/* t_export	*fill_list(char **strs, t_export *ret)
{
	int			i;
	int			len;
	char		*tmp;

	ret->plen = av_amount(strs);
	i = -1;
	while (++i < ret->plen)
	{
		ret->box[i].id = i;
		if (!strs[i])
			return (NULL);
		len = 0;
		while (strs[i][len] && strs[i][len] != '=')
			len++;
		ret->box[i].name = malloc(len + 2);
		ft_strlcpy(ret->box[i].name, strs[i], len + 2);//230525nimai: included until '='
		tmp = ft_substr(strs[i], len + 1, ft_strlen(strs[i]) - len);
		ret->box[i].val = malloc(ft_strlen(strs[i]) - len + 1);
		ft_strlcpy(ret->box[i].val, tmp, ft_strlen(strs[i]) - len + 1);
	}
	return (ret);
} */

/**
 * @brief get absolute path to move
 * @author nimai
 * @param environ I think grab extern char **environ is ilegal, confirmation required
 * @return destination path as string
 */
char	**fake_env(void)
{
	extern char	**environ;
	char		**ret;
	int			i;
	int			plen;

	i = 0;
	plen = av_amount(environ);
	ret = malloc(sizeof(char *) * (plen + 1));
	while (i < plen)
	{
		ret[i] = malloc(ft_strlen(environ[i]) + 1);
		if (!ret[i])
			return (NULL);
		ret[i] = environ[i];
	//	free (val);
		i++;
/* 		val = malloc(ft_strlen(environ[i]) + 1);
		ret[i] = malloc(ft_strlen(environ[i]) + 1);
		if (!val)
			return (NULL);
		val = environ[i];
		if (val)
			ret[i] = val;
		free (val);
		i++; */
	}
	return (ret);
}



/**
 * @brief manage "builtin" export cmd.
 * @author nimai
 * @param **av "export", "ABC=abc".
 * @return 
 */
int	built_export(char **av)
{
	t_export	*list;
	char		**tmp_env;
//	int			i = 0;

	if (av_amount(av) == 2)
	{
		tmp_env = fake_env();
		if (!tmp_env)
		{
			return (printf("ERROR: Line: %d\n", __LINE__), 0);
		}
/* 		while (tmp_env[i])
		{
			list = fill_list(tmp_env);
			i++;
		} */
		list = (t_export *)malloc(sizeof(t_export));
		if (!list)
			return (0);
		list = fill_list(tmp_env, list);
		printf("Line: %d	\n", __LINE__);
		quick_sort(list->box, 0, av_amount(tmp_env) - 1);
		printf("Line: %d	\n", __LINE__);
		output_env(list, av_amount(tmp_env), FLAGEXPORT);
	}
	else if (av_amount(av) == 3)
	{
		//230525nimai: add, function to add variable
	}

//printer
/* 	i = 0;
	while (i < av_amount(tmp_env))
	{
		printf("Line: %d	", __LINE__);
		printf("i	:	%d\n", i);
		printf("name	:	%s\n", list->box[i].name);
		printf("val	:	%s\n", list->box[i].val);
		i++;
	} */
//printer
    return 0;
}

/**
 * BEHAVIOUR IN BASH
 * when execute export, the list should be ascending order, 
 * separated by capital letter and small letter
 * 
 * 
 */
