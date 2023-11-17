/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:11:36 by nimai             #+#    #+#             */
/*   Updated: 2023/11/17 09:55:37 by nimai            ###   ########.fr       */
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
	obtain_pwd_home(data, 1);
	return (0);
}
