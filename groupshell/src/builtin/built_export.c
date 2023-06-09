/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 10:18:56 by nimai             #+#    #+#             */
/*   Updated: 2023/06/09 16:12:22 by nimai            ###   ########.fr       */
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
char	**envp_strs_join(char **input, t_data *data)
{
	char	**ret;
	int		i;
	int		j;

	ret = (char **)malloc(sizeof(char *) * (av_amount(input) + \
							av_amount(data->env) - 2));
	if (!ret)
		return (heap_error(1), NULL);
	i = 0;
	j = 0;
	while (data->env[i])
	{
		ret[i] = data->env[i];
		i++;
	}
	i--;
	while (input[++j])
	{
		if (check_valid(input[j], "export"))
		{
			ret[i] = input[j];
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
int	built_export(char **input, t_data *data)
{
	t_export	*list = NULL;
	char		**tmp_env = NULL;
	char		**av = NULL;
	char		**new_envp = NULL;

//------------------------------------------------------
/* 	int i = -1;
	while (data->env[++i])
		ft_printf("env %d: %s\n", i, data->env[i]);
	i = -1;
	while (input[++i])
		ft_printf("input %d: %s\n", i, input[i]); */

//----------------------------------------------------
	if (av_amount(input) == 1)
	{
		av = input;
		tmp_env = data->env;
		if (!tmp_env || !av)
			return (printf("ERROR: Line: %d\n", __LINE__), 0);
		list = (t_export *)malloc(sizeof(t_export));
		if (!list)
			return (heap_error(1), 0);
		list = fill_list(tmp_env, list);
//		quick_sort(list->box, 0, av_amount(tmp_env) - 1);
		output_env(list, av_amount(tmp_env), FLAGEXPORT);
	}
	else if (av_amount(input) > 1 && input[1][0] == '$')
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
		new_envp = envp_strs_join(input, data);
		if (!new_envp)
			return (printf("ERROR: Line: %d\n", __LINE__));
		data->env = new_envp;
//		tmp_env = data->env;
//printer 
/* 		printf("		===TEST PRINT===\n");
		list = (t_data *)malloc(sizeof(t_data));
		if (!list)
			return (heap_error(1), 0);
		list = fill_list(tmp_env, list);
		quick_sort(list->box, 0, av_amount(tmp_env) - 1);
		output_env(list, av_amount(tmp_env), FLAGEXPORT);
		printf("		===TEST PRINT===\n"); */
/* 		int i = 0;
		while (i < av_amount(data->env))
		{
			ft_printf("env %d: %s\n", i, data->env[i]);
			i++;
		} */
/* 		i = -1;
		while (input[++i])
			ft_printf("input %d: %s\n", i, input[i]); */
		
//printer
	}


//230609comment to check
/* 	if (list)
		arr_free(list); */
	free (list);
//	free (new_envp);
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
