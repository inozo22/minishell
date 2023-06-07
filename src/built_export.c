/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 10:18:56 by nimai             #+#    #+#             */
/*   Updated: 2023/06/07 14:59:26 by nimai            ###   ########.fr       */
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
				if (ft_strlen(list->box[i].val) >= 1)
					ft_printf("\"%s\"", list->box[i].val);
				ft_printf("\n");
			}
		}
		if (flag == FLAGENV && i == len - 1)
			break ;
	}
}

/**
 * @brief initiation t_export
 * @author nimai
 * @param name it will include until "="
 * @note It's not beautiful to allocate 2000 each box[i].name and val, but it's necessary to sort.
 */
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
		while (strs[i][len] != '=')
			len++;
		ret->box[i].name = ft_calloc(1, 2000);
		ret->box[i].val = ft_calloc(1, 2000);
		if (!ret->box[i].name || !ret->box[i].val)
			return (NULL);
		ft_strlcpy(ret->box[i].name, strs[i], len + 2);
		tmp = ft_substr(strs[i], len + 1, ft_strlen(strs[i]) - len);
		ft_strlcpy(ret->box[i].val, tmp, ft_strlen(strs[i]) - len + 1);
		free (tmp);
	}
	return (ret);
}

/**
 * @brief add environment according to av in **
 * @author nimai
 * @return ** pointer, then free 
 * @note 230530nimai: I will throw it away
 */
char	**envp_strs_join(t_temp *temp)
{
	char	**ret;
	int		i;
	int		j;

	ret = (char **)malloc(sizeof(char *) * (av_amount((char **)temp->argv) + \
	av_amount((char **)temp->envp) - 2));
	if (!ret)
		return (heap_error(1), NULL);
	i = 0;
	j = 1;
	while (temp->envp[i])
	{
		ret[i] = temp->envp[i];
		i++;
	}
	i--;
	while (temp->argv[++j])
	{
		if (check_valid(temp->argv[j], "export"))
		{
			ret[i] = temp->argv[j];
			i++;
		}
	}
	return (ret);
}

/**
 * @brief manage "builtin" export cmd.
 * @author nimai
 * @param **av "export", "ABC=abc".
 * @return 
 */
int	built_export(t_temp *temp)
{
	t_export	*list = NULL;
	char		**tmp_env = NULL;
	char		**av = NULL;
	char		**new_envp = NULL;

	if (av_amount((char **)temp->argv) == 2)
	{
		av = (char **)temp->argv;
		tmp_env = (char **)temp->envp;
		if (!tmp_env || !av)
			return (printf("ERROR: Line: %d\n", __LINE__), 0);
		list = (t_export *)malloc(sizeof(t_export));
		if (!list)
			return (heap_error(1), 0);
		list = fill_list(tmp_env, list);
		quick_sort(list->box, 0, av_amount(tmp_env) - 1);
		output_env(list, av_amount(tmp_env), FLAGEXPORT);
	}
	else if (av_amount((char **)temp->argv) > 2 && temp->argv[2][1] == '$')
	{
		//=>I have to print the variable, if doesn't ex
/* 		if ()//match to some variable, print
			;
		else */
		output_env(list, av_amount(tmp_env), FLAGEXPORT);
		/**
		 * 230601nimai: it's required to have some flag to know if it's a given path
		 */
	}
	else
	{
		new_envp = envp_strs_join(temp);
		if (!new_envp)
			return (printf("ERROR: Line: %d\n", __LINE__));
		temp->envp = new_envp;
		tmp_env = (char **)temp->envp;
//printer 
		printf("		===TEST PRINT===\n");
		list = (t_export *)malloc(sizeof(t_export));
		if (!list)
			return (heap_error(1), 0);
		list = fill_list(tmp_env, list);
		quick_sort(list->box, 0, av_amount(tmp_env) - 1);
		output_env(list, av_amount(tmp_env), FLAGEXPORT);
		printf("		===TEST PRINT===\n");
//printer 
	}
	arr_free(list);
	free (list);
	free (new_envp);
	return (0);
}

/**
 * BEHAVIOUR ON BASH
 * when execute export, the list should be ascending order, 
 * separated by capital letter and small letter-> done
 * If there is more than one argument after command, add as a variable, 
 * except if there is no space
 * 
 * 230601nimai: I have doubt with $<variable name>
 * 
 * ??? Is it OK if we control in the minishell?	-> OK!
 * For example, it's ok if do sth in bash, but doesn't affect to the minishell? ->OK!
 * 
 */
