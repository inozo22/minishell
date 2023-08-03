/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msgs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-mada <bde-mada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 16:04:56 by bde-mada          #+#    #+#             */
/*   Updated: 2023/06/24 22:23:08 by bde-mada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	error_file(char *prog_name, char *in_file)
{
	ft_putstr_fd(prog_name, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(in_file, 2);
	if (errno == 13)
	{
		ft_putendl_fd(": Permission denied", 2);
		return (127);
	}
	ft_putendl_fd(": No such file or directory", 2);
	return (127);
}

int	error_msg(char *prog_name, char *cmd, int mode)
{
	ft_putstr_fd(prog_name, 2);
	ft_putstr_fd(": ", 2);
	if (mode == 1)
	{
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": command not found", 2);
		return (127);
	}
	if (mode == 2)
	{
		ft_putstr_fd(": syntax error near unexpected token `", 2);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd("'", 2);
		return (2);
	}
	return (0);
}
