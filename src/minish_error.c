/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:30:52 by nimai             #+#    #+#             */
/*   Updated: 2023/05/15 11:38:33 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minish_error(const char *cmd, const char *msg)
{
	write(STDERR_FILENO, "minishell: ", 11);
	if (cmd)
		write(STDERR_FILENO, cmd, ft_strlen(cmd));
	write(STDERR_FILENO, ": ", 2);
	if (msg)
		write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, "\n", 1);
}

void	minish_error_exit(int status, const char *cmd, const char *msg)
{
	minish_error(cmd, msg);
	exit(status);
}

