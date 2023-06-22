/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:11:50 by nimai             #+#    #+#             */
/*   Updated: 2023/06/22 10:26:24 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <regex.h>

/**
 * @brief when push Ctrl + D, exit 
 * @note as the super free after the while, only write "exit" and break the loop
 */
void	sig_eof(void)
{
	write(STDOUT_FILENO, "exit\n", 5);
}

void	action(int sig)
{
	char	*str;
	char	*str2;

	str = "\t\t\t\b\b\b\b\b                                                        ";
	str2 = "                             \n";
	(void)sig;
	rl_on_new_line();
	write(1, str, 54);
	write(1, str2, 30);
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
