/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:49:51 by nimai             #+#    #+#             */
/*   Updated: 2023/05/04 17:12:06 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int	main(int ac, char **av)
{
	int	id = fork();

	if (id == 0)
	{
		sleep(1);
	}
	printf("Returned by fork: %d, Current ID: %d, parent ID: %d\n", id, getpid(), getppid());

	int res = wait(NULL);

	if (res == -1)
	{
		printf("No children to wait for\n");
	}
	else
	{
		printf("%d finished execution\n", res);
	}

	return (0);
}




/* #define FILE_PATH "./test.dat"

int	main(void)
{
	if (access(FILE_PATH, (R_OK | X_OK)))
	{
		perror ("access");
		return -1;
	}
	printf("Confirm result (R_OK | X_OK): PASS!\n");
	return 0;
}
 */
/* int	main(void)
{
	char *line = NULL;

	while (1)
	{
		line = readline("> ");
		if (line == NULL || strlen(line) == 0)
		{
			free(line);
			break;
		}
		printf("Line is '%s'\n", line);
	//	add_history(line);
		free(line);
	}
	printf("exit\n");
	return (0);
}
 */