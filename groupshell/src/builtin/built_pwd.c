/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-mada <bde-mada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:11:36 by nimai             #+#    #+#             */
/*   Updated: 2023/06/08 17:18:06 by bde-mada         ###   ########.fr       */
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
int	built_pwd(t_data *data)
{
	char	*mycwd;

	(void)data;
	mycwd = getcwd(NULL, 0);
	ft_printf("%s\n", mycwd);
	free (mycwd);
	return (0);
	//230523nimai: should be managed the flags? (at least give some message?)
}
