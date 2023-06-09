/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:11:36 by nimai             #+#    #+#             */
/*   Updated: 2023/06/01 13:42:59 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief manage "builtin" pwd cmd.
 * @author nimai
 * @param **av "pwd"
 * @return if there are sth after cmd, ignore and execute it normally. Don't manage any flags.
 * @note getcwd allocate mamory when it's executed, so it should be freed
 */
int	built_pwd(t_temp *temp)
{
	char	*mycwd;

	(void)temp;
	mycwd = getcwd(NULL, 0);
	ft_printf("%s\n", mycwd);
	free (mycwd);
	return (0);
	//230523nimai: should be managed the flags? (at least give some message?)
}
