/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_signal_handling.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 10:48:37 by nimai             #+#    #+#             */
/*   Updated: 2023/09/06 15:43:51 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <signal.h>
// #include <sys/ioctl.h>
// #include <string.h>
// #include <unistd.h>
// #include <stdlib.h>
// #include <stdio.h>
// #include <sys/wait.h>
// #include <sys/types.h>

// // void	action(int sig)
// // {
// // 	if (sig == SIGINT)
// // 	{
// // 		write(STDOUT_FILENO, "^Cdad\n", 5);
// // 	}
// // }

// // void	set_signal_handlers(pid_t pid)
// // {
// // 	struct sigaction	sa;

// // 	bzero(&sa, sizeof(struct sigaction));
// // 	if (pid)
// // 	{
// // 		sa.sa_sigaction = action;
// // 		sigemptyset(&sa.sa_mask);
// // 	//	sa.sa_flags = SA_SIGINFO;
// // 		sigaction(SIGINT, &sa, NULL);

// // 	}
// // }

// void	action(int sig, siginfo_t *info, void *ucontext)
// {
// 	(void)ucontext;
// 	//(void)info;

// 	if (sig == SIGINT && info->si_pid == 0)
// 		write(1, "Success\n", 8);
// 	if (sig == SIGINT)
// 	{
// 		write(1, "Success in pappy\n", 17);
// 	}
// }

// void	set_signal_handlers(pid_t pid)
// {
// 	struct sigaction	sa;

// 	// printf("pid: %d\n", info->si_pid);
// 	if (pid == 13)
// 	{
// 		printf("pappy process\n");
// 		bzero(&sa, sizeof(struct sigaction));
// 		sa.sa_sigaction = action;
// 		sigemptyset(&sa.sa_mask);
// 		sa.sa_flags = SA_SIGINFO;
// 		sigaction(SIGINT, &sa, NULL);
// 	}
// 	else if (pid == 0)
// 	{
// 		printf("kid process\n");
// 		bzero(&sa, sizeof(struct sigaction));
// 		sa.sa_sigaction = action;
// 		sigemptyset(&sa.sa_mask);
// 		sa.sa_flags = SA_SIGINFO;
// 		sigaction(SIGINT, &sa, NULL);
// 	}
// }

// // int main(void)
// // {
// // 	set_signal_handlers(action);
// // //	set_signal_handlers(13);
// //     while (1)
// //     {
// //         ;
// //     }
// // 	exit (0);
// //     return (0);
// // }

// int main(void) 
// {
// 	pid_t pid;

// 	set_signal_handlers(13);
// //	set_signal_handlers(pid);
// 	pid = fork(); // Create a child process
// 	if (pid < 0)
// 	{
// 		perror("Fork failed");
// 		exit(EXIT_FAILURE);
// 	}
// 	else if (pid == 0)// Child process
// 	{
// 		set_signal_handlers(pid);
// 	// Execute the 'cat' command in the child process
// 		execlp("cat", "cat", NULL);
// 	// If execlp() fails, it will only reach this point
// 		perror("execlp");
// 		exit(EXIT_FAILURE);
// 	}
// 	else
// 	{ // Parent process
// 		// Wait for the child to finish
// 		int status;
// 		waitpid(pid, &status, 0);
// 		while (1)
// 		{
// 			;
// 		}

// 		if (WIFEXITED(status))
// 		{
// 			printf("Child process exited with status %d\n", WEXITSTATUS(status));
// 		}
// 		else
// 		{
// 			printf("Child process did not exit normally\n");
// 		}
// 	}
// 	return 0;
// }


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "include/minishell.h"

#define MAX_INPUT_SIZE 1024

void	*del(void **ptr)
{
	free(*ptr);
	ptr = NULL;
	return (ptr);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}


char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	int		len;
	char	*sjoin;

	i = -1;
	j = -1;
	len = 0;
	if (s1)
		len += ft_strlen((char *)s1);
	if (s2)
		len += ft_strlen((char *)s2);
	sjoin = (char *)malloc((len + 1) * sizeof(char));
	if (!sjoin)
		return (NULL);
	while (s1 && s1[++i])
		sjoin[i] = s1[i];
	if (!s1)
		++i;
	while (s2 && s2[++j])
		sjoin[i + j] = s2[j];
	sjoin[i + j] = '\0';
	return (sjoin);
}


int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1)
	{
		if (!s2)
			return (0);
		else
			return (-s2[0]);
	}
	else if (!s2)
		return (*s1);
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	here_doc_to_stdin(char *input)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		return (1);
	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		close(fd[READ_END]);
		write(fd[WRITE_END], input, ft_strlen(input));
		close(fd[WRITE_END]);
		exit(0);
	}
	close(fd[WRITE_END]);
	dup2(fd[READ_END], STDIN_FILENO);
	close(fd[READ_END]);
	return (0);
}

int	here_doc_read(char *eof)
{
	char	*line_read;
	char	*input;
	char	*tmp;

	input = NULL;
	while (1)
	{
		line_read = readline(">");
		if (ft_strcmp(eof, line_read))
			break ;
		tmp = input;
		input = ft_strjoin(line_read, input);
		free(tmp);
		del((void **)&line_read);
	}
	del((void **)&line_read);
	return (here_doc_to_stdin(input));
}

int main() 
{
    char input[MAX_INPUT_SIZE];

    while (1) 
	{
        printf("SimpleShell> ");
        fgets(input, MAX_INPUT_SIZE, stdin);

        // Remove the trailing newline character
        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "exit") == 0) 
		{
            printf("Exiting SimpleShell...\n");
            break;
        }

        pid_t pid = fork();
        if (pid < 0) 
		{
            perror("Fork failed");
            exit(EXIT_FAILURE);
        } 
		else if (pid == 0) 
		{ // Child process
            char *args[] = {"/bin/sh", "-c", input, NULL};
            execvp("/bin/sh", args);
            perror("Exec failed");
            exit(EXIT_FAILURE);
        } 
		else 
		{ // Parent process
            int status;
            waitpid(pid, &status, 0);
            if (WIFEXITED(status)) 
			{
                printf("Child process exited with status %d\n", WEXITSTATUS(status));
            } 
			else 
			{
                printf("Child process did not exit normally\n");
            }
        }
    }

    return 0;
}
