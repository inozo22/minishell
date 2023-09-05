/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-mada <bde-mada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:11:36 by nimai             #+#    #+#             */
/*   Updated: 2023/09/05 16:28:12 by bde-mada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @author nimai
 * @param pwd from the built_cd
 * @return if there are sth after cmd, ignore and execute it normally.
 * Don't manage any flags.
 * @note obtain pwd from static pwd in built_cd. So you can also obtain
 * after unset PWD
 */
int	built_pwd(t_data *data)
{
	built_cd(NULL, data);
	return (0);
}

/**
 * 230621nimai: do I need this control? at the moment ignore all after CMD.
 * bash-3.2$ pwd !·$%&/()=?
 * bash: !·$%: event not found
 * 
 * 
 * 
 */
