/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:11:50 by nimai             #+#    #+#             */
/*   Updated: 2023/06/05 18:48:21 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	action(int signal, siginfo_t *info, void *ucontext)
{
	
}

void	set_signal_action(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(struct sigaction));
	sa.sa_sigaction = &action;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sigaddset(&sa.sa_mask, SIGQUIT);
	sigaddset(&sa.sa_mask, SIGINT);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);

}

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
 * 　読み手の無いパイプへの書き出し
 * 
 * SIG_DEL	そのシグナルに対するデフォルトの操作を行う.
 * SIG_IGN	シグナルを無視する.
*/
