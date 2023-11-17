/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:11:50 by nimai             #+#    #+#             */
/*   Updated: 2023/11/17 11:32:56 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @note I think I will remove the strs
 */
void	action_child(int sig, siginfo_t *info, void *context)//looks working this, but don't let me print these lines...
{
	(void)context;
	(void)info;
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "^C\n", 3);
	}
	else if (sig == SIGQUIT)
	{
		write (STDOUT_FILENO, "^\\Quit: 3\n", 10);
	}
	return ;
}

/**
 * @note
 */
void	action(int sig)
{
	if (sig == SIGINT)
	{
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		g_return_val = 1;
	}
}

void	sigquit_ignore(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(struct sigaction));
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
}

/**
 * @note 230915nimai: put sigaction for sigquit in parent process instead of 
 * 		sigquit_ignore to make ctrl+\ change g_return_val and "ignore" the sign
 * @note 230915nimai: The above is a misunderstanding. Revert to original.
 */
void	set_signal_handlers(pid_t pid)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(struct sigaction));
	if (pid)
	{
		write(1, "I'm pappy\n", 10);
		sigquit_ignore();
		sa.sa_handler = &action;
		sa.sa_flags = SA_SIGINFO | SA_RESTART;
		sigaction(SIGINT, &sa, NULL);
	}
	else
	{
		write(1, "I'm kid\n", 8);
		sa.sa_sigaction = &action_child;
		sa.sa_flags = SA_SIGINFO | SA_RESTART;
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);
	}
}
