/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:11:50 by nimai             #+#    #+#             */
/*   Updated: 2023/09/15 18:23:07 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief when push Ctrl + D, exit 
 * @note as the super free after the while, only write "exit" and break the loop
 * @note put exit function from builins
 * @note 230915nimai: commented
 */
// void	sig_eof(void)
// {
// 	write(STDOUT_FILENO, "exit\n", 5);
// 	g_return_val = 0;
// }

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
//		g_return_val = 130;
	}
	else if (sig == SIGQUIT)
	{
		write (STDOUT_FILENO, "^\\Quit: 3\n", 10);
//		g_return_val = 131;
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
	//	rl_redisplay();
		g_return_val = 1;
		// write(1, "ctrl+C push\n", 12);
	}
	// else if (sig == SIGQUIT)
	// {
	// 	rl_redisplay();
	// 	g_return_val = 0;
	// }
}

void	sigquit_ignore(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(struct sigaction));
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
//	g_return_val = 0;
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
		write(1, "Im pappy\n", 9);
		sigquit_ignore();
		sa.sa_handler = &action;
		sa.sa_flags = SA_SIGINFO | SA_RESTART;
		sigaction(SIGINT, &sa, NULL);
		// sigaction(SIGQUIT, &sa, NULL);
	}
	else
	{
		write(1, "Im kid\n", 7);
		sa.sa_sigaction = &action_child;
		sa.sa_flags = SA_SIGINFO | SA_RESTART;
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);
	}
}
