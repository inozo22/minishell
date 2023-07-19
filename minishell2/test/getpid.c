/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getpid.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-mada <bde-mada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 15:32:22 by bde-mada          #+#    #+#             */
/*   Updated: 2023/06/20 15:49:33 by bde-mada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_PID_LENGTH 20

/* int	main(void)
{
	int		fd;
	char	*buffer;
	ssize_t bytesRead;

	fd = open("/proc/self", O_RDONLY);
	if (fd == -1)
		return (-1);
	bytesRead = read(fd, buffer, MAX_PID_LENGTH);
	if (bytesRead <= 0)
		return (-1);
	close(fd);
	printf("PID: %s", buffer);
	while (1);
	return (0);
} */

int	main(void)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
		return (1);
	
	if (pid == 0)
	{
		sleep(10);
		exit(0);
	}
	else
	{
		wait(NULL);
		printf("Pid: %d\n", pid);
	}
	sleep(10);
	return (0);
}