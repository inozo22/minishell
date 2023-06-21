/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:11:50 by nimai             #+#    #+#             */
/*   Updated: 2023/06/21 14:04:06 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief when push Ctrl + D, exit 
 * 
 * 
 * @note 
 */
void	sig_eof(void)
{
	write(STDOUT_FILENO, "exit\n", 5);
	exit (0);
}

void	action(int sig)
{
	(void)sig;
	rl_on_new_line();
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigquit_ignore(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(struct sigaction));
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

void	set_signal_handlers(void)
{
	struct sigaction	sa;

	sigquit_ignore();
	ft_bzero(&sa, sizeof(struct sigaction));
	sa.sa_handler = &action;
	sigaction(SIGINT, &sa, NULL);
}
