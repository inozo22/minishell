/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_signal_handling.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 10:48:37 by nimai             #+#    #+#             */
/*   Updated: 2023/09/06 12:14:11 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <sys/ioctl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>

// void	action(int sig)
// {
// 	if (sig == SIGINT)
// 	{
// 		write(STDOUT_FILENO, "^Cdad\n", 5);
// 	}
// }

// void	set_signal_handlers(pid_t pid)
// {
// 	struct sigaction	sa;

// 	bzero(&sa, sizeof(struct sigaction));
// 	if (pid)
// 	{
// 		sa.sa_sigaction = action;
// 		sigemptyset(&sa.sa_mask);
// 	//	sa.sa_flags = SA_SIGINFO;
// 		sigaction(SIGINT, &sa, NULL);

// 	}
// }

void	action(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	//(void)info;

	if (sig == SIGINT && info->si_pid == 0)
		write(1, "Success\n", 8);
	if (sig == SIGINT)
	{
		write(1, "Success in pappy\n", 17);
	}
}

void	set_signal_handlers(pid_t pid)
{
	struct sigaction	sa;

	// printf("pid: %d\n", info->si_pid);
	if (pid == 13)
	{
		printf("pappy process\n");
		bzero(&sa, sizeof(struct sigaction));
		sa.sa_sigaction = action;
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = SA_SIGINFO;
		sigaction(SIGINT, &sa, NULL);
	}
	else if (pid == 0)
	{
		printf("kid process\n");
		bzero(&sa, sizeof(struct sigaction));
		sa.sa_sigaction = action;
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = SA_SIGINFO;
		sigaction(SIGINT, &sa, NULL);
	}
}

// int main(void)
// {
// 	set_signal_handlers(action);
// //	set_signal_handlers(13);
//     while (1)
//     {
//         ;
//     }
// 	exit (0);
//     return (0);
// }

int main(void) 
{
	pid_t pid;

	set_signal_handlers(13);
//	set_signal_handlers(pid);
	pid = fork(); // Create a child process
	if (pid < 0)
	{
		perror("Fork failed");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)// Child process
	{
		set_signal_handlers(pid);
	// Execute the 'cat' command in the child process
		execlp("cat", "cat", NULL);
	// If execlp() fails, it will only reach this point
		perror("execlp");
		exit(EXIT_FAILURE);
	}
	else
	{ // Parent process
		// Wait for the child to finish
		int status;
		waitpid(pid, &status, 0);
		while (1)
		{
			;
		}

		if (WIFEXITED(status))
		{
			printf("Child process exited with status %d\n", WEXITSTATUS(status));
		}
		else
		{
			printf("Child process did not exit normally\n");
		}
	}
	return 0;
}
