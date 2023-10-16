/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msgs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 16:04:56 by bde-mada          #+#    #+#             */
/*   Updated: 2023/10/16 15:29:20 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	error_file(char *in_file)
{
	ft_putstr_fd(SHELL_NAME": ", 2);
	ft_putstr_fd(in_file, 2);
	if (errno == EACCES)
	{
		ft_putendl_fd(": Permission denied", 2);
		return (127);
	}
	ft_putendl_fd(": No such file or directory", 2);
	return (127);
}

int	error_msg(char *cmd, int mode)
{
	ft_putstr_fd(SHELL_NAME": ", 2);
	if (mode == 2)
	{
		ft_putstr_fd("syntax error near unexpected token `", 2);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd("'", 2);
		return (258);
	}
	ft_putstr_fd(cmd, 2);
	if (mode == 1)
	{
		ft_putendl_fd(": command not found", 2);
		return (127);
	}
	if (mode == 3)
	{
		ft_putendl_fd("is a directory", 2);
		return (126);
	}
	return (0);
}

int	command_not_found_handler(char *name, char *cmd)
{
	ft_putstr_fd(name, 2);
	ft_putstr_fd(": command not found: ", 2);
	ft_putendl_fd(cmd, 2);
	return (127);
}

int	errors(int error_id, t_data *data)
{
	perror(SHELL_NAME);
	if (error_id == ENOMEM)
		ft_printf("Cannot allocate memory\n");
	free_alloc(data);
	return (error_id);
}

/**
 * @note give warning message, but return 0 as successed
 * @param type 1: shlvl
 */
int	warning_message(int type, int num)
{
	if (type == 1)
	{
		ft_putstr_fd(SHELL_NAME": warning: shell level (", 1);
		ft_printf("%d", num);
		ft_putendl_fd(") too high, resetting to 1", 1);
	}
	return (0);
}
