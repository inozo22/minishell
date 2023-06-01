/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 10:18:56 by nimai             #+#    #+#             */
/*   Updated: 2023/06/01 13:52:26 by nimai            ###   ########.fr       */
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
		ret->box[i].name = ft_calloc(1, 2000);
		ret->box[i].val = ft_calloc(1, 2000);
		if (!ret->box[i].name || !ret->box[i].val)
			return (NULL);
		ft_strlcpy(ret->box[i].name, strs[i], len + 2);//230525nimai: included until '='
		tmp = ft_substr(strs[i], len + 1, ft_strlen(strs[i]) - len);
		ft_strlcpy(ret->box[i].val, tmp, ft_strlen(strs[i]) - len + 1);
		free (tmp);
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
	if (!(ft_isalpha(str[i]) || str[i] == '_'))
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
 * @note 230530nimai: I will throw it away
 */
/* t_export	*envp_join(t_temp *t, t_export *list)
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
			if (!list->box[amount].name || !list->box[amount].val)
			{
				return (NULL);
			}
			ft_strlcpy(list->box[amount].name, t->argv[i], len + 2);
			tmp = ft_substr(t->argv[i], len + 1, ft_strlen(t->argv[i]) - len);
			ft_strlcpy(list->box[amount].val, tmp, ft_strlen(t->argv[i]) - len + 1);
		}
	}
	return (list);
}
 */

int	new_amount(t_temp *temp)
{
	int	ret;

	ret = 0;
	while (temp->argv[ret])
	{
		ret++;
	}
	ret += av_amount((char **)temp->envp);
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
	av_amount((char **)temp->envp))) - 2;//minus for "./minishell" and "export"
	//system ("leaks minishell");
	if (!ret)
		return (heap_error(1), NULL);
	i = 0;
	j = 2;
	while (temp->envp[i])
	{
/* 		ret[i] = ft_calloc(1, 2000);
		if (!ret[i])
			return (NULL); */
		ret[i] = temp->envp[i];
		i++;
	}
	i--;
	while (temp->argv[j])
	{
/* 		ret[i] = ft_calloc(1, 2000);
		if (!ret[i])
			return (NULL); */
		ret[i] = temp->argv[j];
		j++;
		ret++;
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
//	int i = 0;

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
		arr_free(list);
		free (list);
	}
	else if (av_amount((char **)temp->argv) > 2 && temp->argv[2][1] == '$')
	{
		//=>I have to print the variavle, if doesn't ex
/* 		if ()//match to some variable, print
			;
		else */
			output_env(list, av_amount(tmp_env), FLAGEXPORT);
	}
	else//230525nimai: add, function to add variable
	{
		//no leaks
		new_envp = envp_strs_join(temp);
		//41 leaks
		if (!new_envp)
			return (printf("ERROR: Line: %d\n", __LINE__));
		//strs_free((char **)temp->envp);
		temp->envp = new_envp;
		//new_envp = strs_free(new_envp);
		//check printer
		tmp_env = (char **)temp->envp;
		printf("		===TEST PRINT===\n");
		list = (t_export *)malloc(sizeof(t_export));
		if (!list)
			return (heap_error(1), 0);
		list = fill_list(tmp_env, list);
		quick_sort(list->box, 0, av_amount(tmp_env) - 1);
		output_env(list, av_amount(tmp_env), FLAGEXPORT);
		//strs_free(new_envp);
		//free (new_envp);
		arr_free(list);
		free (list);
	//	ptr_free ((void **)tmp_env);
		printf("		===TEST PRINT===\n");
		//check printer

	}
	//all_tmp_free (temp);
	return (0);
}

/**
 * BEHAVIOUR ON BASH
 * when execute export, the list should be ascending order, 
 * separated by capital letter and small letter-> done
 * If there is more than one argument after command, add as a variable, 
 * except if there is no space
 * 
 * ??? Is it OK if we control in the minishell?	-> OK!
 * For example, it's ok if do sth in bash, but doesn't affect to the minishell? ->OK!
 * 
 */
