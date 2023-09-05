/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_return_signal.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-mada <bde-mada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:52:25 by bde-mada          #+#    #+#             */
/*   Updated: 2023/09/04 17:31:59 by bde-mada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>

int	main(void)
{
	int return_val;
	char *args[2] = {".", NULL};
	pid_t pid = fork();
	if (!pid)
	{	
		printf("Child process\n");
		if (execve("/bin/cat", NULL, NULL) == -1)
			exit (1);
	}
	else
	{	
		usleep(100);
		printf("Parent process\n");
		waitpid(0, &return_val, 0);
		printf("Exit status: %d\n", return_val);
	}
	return 0;
}