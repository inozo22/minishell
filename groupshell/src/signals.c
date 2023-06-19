/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:11:50 by nimai             #+#    #+#             */
/*   Updated: 2023/06/19 16:12:19 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* #include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h> */

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

/* 		if (signal(SIGINT, &sig_int_input) == SIG_ERR)
		{
			ft_printf("Line: %d, ERROR\n", __LINE__);
			exit (1);
		}
		else if (signal(SIGQUIT, &sig_quit_input) == SIG_ERR)
		{
			ft_printf("Line: %d, ERROR\n", __LINE__);
			exit (1);
		} */

/* void	sig_int_input(int code)
{
	(void)code;
	ft_putstr_fd("\b\b  ",2);
	ft_putstr_fd("\n", 2);
}

void	sig_quit_input(int code)
{
	(void)code;
	printf("Line: %d, File: %s\n", __LINE__, __FILE__);
	ft_putstr_fd("\b\b \b\n", STDERR_FILENO);
} */

void	sigint_sighandler(int sig)
{
	(void)sig;
	rl_on_new_line();
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_redisplay();
}

/**
 * 
 * 
 * 
 * @note SIGQUIT - SIG_IGN working, SIGINT - sighandler more or less ... Ctrl + D is not signal but it's EOF, so...?
 */
void	set_signal_handlers(void)
{
	if (signal(SIGINT, &sigint_sighandler) == SIG_ERR || signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	{
		ft_printf("Line: %d, ERROR\n", __LINE__);
		exit (1);
	}
}

/* void	action(int signal, siginfo_t *info, void *ucontext)
{
	
}

void	set_signal_action(void)
{
	struct sigaction	sa;

	bzero(&sa, sizeof(struct sigaction));
	sa.sa_sigaction = &action;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sigaddset(&sa.sa_mask, SIGQUIT);
	sigaddset(&sa.sa_mask, SIGINT);
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		
	}
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
	{
		
	}

} */

/**
 * rl_clear_history
 * rl_on_new_line
 * rl_replace_line
 * rl_redisplay
 * SIGINT	 2	Terminate	キーボードからの割り込み (Interrupt)
 * SIGQUIT	 3	Terminate	キーボードによる中止 (Quit)
 * SIGKILL	 9	Terminate	Kill シグナル
 * SIGSEGV	11	Core		不正なメモリー参照
 * SIGPIPE	13	Terminate	パイプ破壊:
 * 読み手の無いパイプへの書き出し
 * 
 * SIG_DEL	そのシグナルに対するデフォルトの操作を行う.
 * SIG_IGN	シグナルを無視する.
*/


/* int	main(void)
{
	printf("PID: %d\n", getpid());
	set_signal_action();
	while (1)
		pause ();
	return (0);
} */

/**
 * $ stty -a
 * speed 38400 baud; 31 rows; 217 columns;
lflags: icanon isig iexten echo echoe echok echoke -echonl echoctl
        -echoprt -altwerase -noflsh -tostop -flusho pendin -nokerninfo
        -extproc
iflags: -istrip icrnl -inlcr -igncr ixon -ixoff ixany imaxbel iutf8
        -ignbrk brkint -inpck -ignpar -parmrk
oflags: opost onlcr -oxtabs -onocr -onlret
cflags: cread cs8 -parenb -parodd hupcl -clocal -cstopb -crtscts -dsrflow
        -dtrflow -mdmbuf
cchars: discard = ^O; dsusp = ^Y; eof = ^D; eol = <undef>;
        eol2 = <undef>; erase = ^?; intr = ^C; kill = ^U; lnext = ^V;
        min = 1; quit = ^\; reprint = ^R; start = ^Q; status = ^T;
        stop = ^S; susp = ^Z; time = 0; werase = ^W;
  */

