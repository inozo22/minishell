/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 09:50:16 by nimai             #+#    #+#             */
/*   Updated: 2023/05/26 13:27:32 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief output all list
 * @author nimai
 * @note maybe adjust to some list too.
 */


/**
 * @brief temporary error management
 * @author nimai
 * @note when decided error management, merge it.
 */
void	error_env(char *cmd)
{
	ft_printf("minishell: env: %s: Dunno\n", cmd);
}

/**
 * @brief check if the path exists.
 * @author nimai
 * @note 
 */


/**
 * @brief get absolute path to move
 * @author nimai
 * @param environ I think grab extern char **environ is ilegal, confirmation required
 * @return destination path as string
 */




/**
 * @brief manage "builtin" env cmd.
 * @author nimai
 * @param **av "env", no flags, no arguments
 * @return 
 */
int	built_env(char **av)
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
		printf("Line: %d\n", __LINE__);
		printf("Line: %d\n", __LINE__);
		output_env(list, av_amount(tmp_env), FLAGENV);
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
 * when execute env, the list is not ordered 
 * 
 * 
 */