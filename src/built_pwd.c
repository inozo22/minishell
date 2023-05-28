/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:11:36 by nimai             #+#    #+#             */
/*   Updated: 2023/05/28 09:33:57 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief manage "builtin" pwd cmd.
 * @author nimai
 * @param **av "pwd"
 * @return if there are sth after cmd, ignore and execute it normally. Don't manage any flags.
 */
int	built_pwd(char **av)
{
	(void)av;
	ft_printf(getcwd(NULL, 0));
	ft_printf("\n");
	system("leaks minishell");
	return (0);
	//230523nimai: should be managed the flags? (at least give some message?)
}
