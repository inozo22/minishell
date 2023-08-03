/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:21:14 by nimai             #+#    #+#             */
/*   Updated: 2023/08/03 11:55:33 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>

void	set_signal_handlers(pid_t pid);
void	sig_eof(void);
void	action(int sig);
void	set_signal_exacuting_handlers(void);

#endif
