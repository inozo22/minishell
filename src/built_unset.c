/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 09:50:35 by nimai             #+#    #+#             */
/*   Updated: 2023/05/30 12:46:18 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief temporary error management
 * @author nimai
 * @note when decided error management, merge it.
 */
void	error_unset(char *cmd)
{
	ft_printf("minishell: unset: %s\n", cmd);
}

/**
 * @brief string checker.
 * @author nimai
 * @return 1 if it's valid, otherwise 0.
 * @note doesn't work, CHECK
 */
int	check_valid(char *str)
{
	int	i;

	i = 0;
	if (!(ft_isalpha(str[i]) || str[i] == '_'))
	{
		printf("Line: %d\n", __LINE__);
		return (0);
	}		
	while (str[i])
	{
		if (!(ft_isalnum(str[i] || str[i] == '_')))
		{
			printf("Line: %d\n", __LINE__);
			return (0);
		}
		i++;
	}
	return (1);
}
int	unset_env(char *str)
{
	printf("%s: confirmation required.\n", str);
	
	return (0);
}

/**
 * @brief manage "builtin" unset cmd.
 * @author nimai
 * @param **av "unset", "ABC", "DEF"
 * @return 
 */
int	built_unset(t_temp *temp)
{
	int		i;
	char	**av;

	av = (char **)temp->argv;
	i = 2;
	while (av[i])
	{
		if (check_valid(av[i]) == 1)
			unset_env(av[i]);
		else
		{
			error_unset("Invalid identifier");
			return (1);
		}
		i++;
	}
	return (0);
}

/**
 * BEHAVIOUR IN BASH
 * when execute env, the list is not ordered 
 * 
 * 
 * MEMORY LEAKS
 * 230526nimai: When I try free it, receive errors say that I'm trying free memory which is not allocated.
 * But yes, allocated.
 * 
 */
