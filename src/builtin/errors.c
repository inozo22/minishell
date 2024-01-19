/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 17:20:27 by nimai             #+#    #+#             */
/*   Updated: 2023/11/17 11:01:31 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief get absolute path to move
 * @author nimai
 * @return destination path as string
 */
void	heap_error(int flag)
{
	if (flag == 1)
	{
		ft_printf("memory allocate failure\n");
	}
}

/**
 * @brief error message in builtin with argument
 * @author nimai
 * @note when decided error management, merge it.
 * @note builtin global function
 */
void	error_id_built(char *cmd, char *av, char *comment)
{
	ft_putstr_fd(SH_NAME": ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(av, 2);
	ft_putstr_fd("': ", 2);
	ft_putendl_fd(comment, 2);
}

/**
 * @brief error message in builtin with argument
 * @author nimai
 * @note when decided error management, merge it.
 * @note builtin global function
 */
void	error_av_built(char *cmd, char *av, char *comment)
{
	ft_putstr_fd(SH_NAME": ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(av, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(comment, 2);
}

/**
 * @brief error message in builtin with argument
 * @author nimai
 * @note when decided error management, merge it.
 * @note builtin global function
 */
void	error_built(char *cmd, char *comment)
{
	ft_putstr_fd(SH_NAME": ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	if (errno == 13)
	{
		ft_putendl_fd(": Permission denied", 2);
	}
	ft_putendl_fd(comment, 2);
}

/**
 * @brief error message in builtin with argument
 * @author nimai
 * @note when decided error management, merge it.
 * @note builtin global function
 */
int	error_notset(char *cmd, char *input)
{
	ft_putstr_fd(SH_NAME": ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	if (errno == 13)
	{
		ft_putendl_fd(": Permission denied", 2);
		return (127);
	}
	ft_putstr_fd(input, 2);
	ft_putendl_fd(" not set", 2);
	return (1);
}
