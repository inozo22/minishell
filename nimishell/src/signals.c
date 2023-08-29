/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-mada <bde-mada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:11:50 by nimai             #+#    #+#             */
/*   Updated: 2023/08/29 15:47:26 by bde-mada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief when push Ctrl + D, exit 
 * @note as the super free after the while, only write "exit" and break the loop
 */
void	sig_eof(t_data *data)
{
	write(STDOUT_FILENO, "exit\n", 5);
	data->return_val = 0;
}

/**
 * @note I think I will remove the strs
 */
void	action_child(int sig)//looks working this, but don't let me print these lines...
{
	if (sig == SIGINT)
	{
//		write(STDOUT_FILENO, "^C\n", 3);
		g_return_val = 130;
	}
	else if (sig == SIGQUIT)
	{
		write (STDOUT_FILENO, "^\\Quit: 3\n", 10);
		g_return_val = 131;
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
	}
}

void	sigquit_ignore(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(struct sigaction));
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
	g_return_val = 0;
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
