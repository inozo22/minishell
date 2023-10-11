/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:11:36 by nimai             #+#    #+#             */
/*   Updated: 2023/10/11 12:07:03 by nimai            ###   ########.fr       */
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
int	built_pwd(char **env)
{
	obtain_pwd_home(env, 1);
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
