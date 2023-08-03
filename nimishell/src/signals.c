/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:11:50 by nimai             #+#    #+#             */
/*   Updated: 2023/08/03 12:05:39 by nimai            ###   ########.fr       */
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
void	action_sigquit(int sig)//looks working this, but don't let me print these lines...
{
	(void)sig;
	// write (1, "Got sigquit\n", 12);
	// write (1, "Quit: 3\n", 8);
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
		write (1, "Got sigquit\n", 12);
		write (1, "Quit: 3\n", 8);
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
		write(1, "Im kid\n", 7);
		sa.sa_handler = &action;//SIG_DFL;
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);
	}
}

void	set_signal_exacuting_handlers(void)
{
	struct sigaction	sa;

//	sigquit_ignore();
	ft_bzero(&sa, sizeof(struct sigaction));
	sa.sa_handler = &action_sigquit;
	sigaction(SIGQUIT, &sa, NULL);
//	sigaction(SIGINT, &sa, NULL);
}

