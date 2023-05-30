/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 10:18:56 by nimai             #+#    #+#             */
/*   Updated: 2023/05/30 14:45:58 by nimai            ###   ########.fr       */
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

/**
 * @brief initiation t_export
 * @author nimai
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
		while (strs[i][len] != '=')/* strs[i][len] &&  */
			len++;
		ret->box[i].name = malloc(2000);
		ret->box[i].val = malloc(2000);
		if (!ret->box[i].name || !ret->box[i].val)
			return (NULL);
		ft_strlcpy(ret->box[i].name, strs[i], len + 2);//230525nimai: included until '='
		tmp = ft_substr(strs[i], len + 1, ft_strlen(strs[i]) - len);
		ret->box[i].val = malloc(2000);
		ft_strlcpy(ret->box[i].val, tmp, ft_strlen(strs[i]) - len + 1);
	}
	return (ret);
}

/**
 * @brief get absolute path to move
 * @author nimai
 * @param environ I think grab extern char **environ is illegal, confirmation required
 * @return destination path as string
 * @note 230530nimai: I will not use this function.
 */
/* char	**fake_env(void)
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
		free (ret[i]);//no se de verdad que está pasando aquí
		if (!ret[i])
			return (NULL);
		ret[i] = environ[i];
		i++;
	}
	return (ret);
}
 */


/**
 * @brief check thhe variable name.
 * @author nimai
 * @param environ I think grab extern char **environ is illegal, confirmation required
 * @return destination path as string
 * @note 230530nimai: I will not use this function.
 */
int	check_av_add_envp(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]))
		return (0);
	while (++i < (int)ft_strlen(str))
	{
		if (str[i] == '=')
		{
			return (2);
		}
		if (!ft_isalnum(str[i]))
		{
			return (0);			
		}
	}
	return (1);
}

/**
 * @brief add environment according to av
 * @author nimai
 * @return t_temp pointer
 * @note 230530nimai: better use calloc instead of malloc
 */
t_temp	*envp_join(t_temp *t, t_export *list)
{
	//char	*pmem;
	int		i;
	int		amount;
	int		len;
	char	*tmp;

	i = 1;
	amount = av_amount((char **)t->envp);
	while (++i < av_amount((char **)t->argv))
	{
		if (!check_av_add_envp(t->argv[i]))
			ft_printf("export: `%s': not a valid identifier\n", t->argv[i]);
		else if (check_av_add_envp(t->argv[i]) == 1)//add only variable
		{
			;
		}
		else if (check_av_add_envp(t->argv[i]) == 2)//add variable and valor
		{
			len = 0;
			while (t->argv[i][len] != '=')
				len++;
			list->box[amount].id = amount;
			list->box[amount].name = malloc(2000);
			list->box[amount].val = malloc(2000);
			if (!list->box[amount].name || list->box[amount].val)
				return (NULL);
			ft_strlcpy(list->box[amount].name, t->argv[i], len + 2);
			tmp = ft_substr(t->argv[i], len + 1, ft_strlen(t->argv[i]) - len);
			ft_strlcpy(list->box[amount].val, tmp, ft_strlen(t->argv[i]) - len + 1);
		}
	}
	return (t);
}


/**
 * @brief manage "builtin" export cmd.
 * @author nimai
 * @param **av "export", "ABC=abc".
 * @return 
 */
int	built_export(t_temp *temp)
{
	t_export	*list;
	char		**tmp_env;
	char		**av;

	av = (char **)temp->argv;
	tmp_env = (char **)temp->envp;
	if (!tmp_env || !av)
		return (printf("ERROR: Line: %d\n", __LINE__), 0);
	list = (t_export *)malloc(sizeof(t_export));
	if (!list)
		return (heap_error(1), 0);
	list = fill_list(tmp_env, list);
	if (av_amount(av) == 2)
	{
		quick_sort(list->box, 0, av_amount(tmp_env) - 1);
		output_env(list, av_amount(tmp_env), FLAGEXPORT);
	}
	else if (av_amount(av) > 2 && av[2][1] == '$')
	{
		//=>I have to print the variavle, if doesn't ex
/* 		if ()//match to some variable, print
			;
		else */
			output_env(list, av_amount(tmp_env), FLAGEXPORT);
	}
	else//230525nimai: add, function to add variable
	{
		if (!envp_join(temp, list))
			return (printf("ERROR: Line: %d\n", __LINE__));
	}
	printf("\n===TEST PRINT===\n");
	quick_sort(list->box, 0, av_amount(tmp_env) + av_amount(av) - 1);
	output_env(list, av_amount(tmp_env), FLAGEXPORT);
	return (0);
}

/**
 * BEHAVIOUR IN BASH
 * when execute export, the list should be ascending order, 
 * separated by capital letter and small letter
 * If there is more than one argument after command, add as a variable, 
 * except if there is no space
 * 
 * ??? Is it OK if we control in the minishell?	-> OK!
 * For example, it's ok if do sth in bash, but doesn't affect to the minishell? ->OK!
 * 
 */
