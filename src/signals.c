/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:11:50 by nimai             #+#    #+#             */
/*   Updated: 2023/05/29 16:10:01 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_signal_action(void)
{
	struct sigaction	sa;

    ft_bzero(&sa, sizeof(sa));
	sa.sa

}

/**
 * rl_clear_history
 * rl_on_new_line
 * rl_replace_line
 * rl_redisplay
 * 
*/
