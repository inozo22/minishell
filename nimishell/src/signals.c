/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:11:50 by nimai             #+#    #+#             */
/*   Updated: 2023/08/08 13:09:18 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// #include <termios.h>

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
void	action_child(int sig)//looks working this, but don't let me print these lines...
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "^C\n", 3);
	}
	else if (sig == SIGQUIT)
	{
		write (STDOUT_FILENO, "Quit: 3\n", 8);
	}
	return ;
}

/**
 * @note I think I will remove the strs
 */
void	action(int sig)
{
	if (sig == SIGINT)
	{
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
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
		sa.sa_handler = &action_child;
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);
	}
}
