/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:11:50 by nimai             #+#    #+#             */
/*   Updated: 2023/07/11 15:28:32 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief when push Ctrl + D, exit 
 * @note as the super free after the while, only write "exit" and break the loop
 */
void	sig_eof(void)
{
	write(STDOUT_FILENO, "exit\n", 5);
}

/**
 * @note I think I will remove the strs
 */
void	action(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		write (1, "\n", 1);
	}
}

void	sigquit_ignore(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(struct sigaction));
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

void	set_signal_handlers(pid_t pid)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(struct sigaction));
	if (pid)
	{
		sigquit_ignore();
		sa.sa_handler = &action;
		sigaction(SIGINT, &sa, NULL);
	}
	else
	{
		sa.sa_handler = &action;
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);
	}
}

/* void	set_signal_exacuting_handlers(void)
{
	struct sigaction	sa;

	if (pid == 0)
	{
		sigquit_ignore();
		ft_bzero(&sa, sizeof(struct sigaction));
		sa.sa_handler = &action;
		sigaction(SIGINT, &sa, NULL);
	}
}
 */
