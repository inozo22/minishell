/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:49:51 by nimai             #+#    #+#             */
/*   Updated: 2023/05/15 18:50:35 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
//#include <readline/readline.h>
//#include <readline/history.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <errno.h>

#define PROCESS_NUM 3

#include <stdio.h>
//#include <readline/readline.h>
//#include <readline/history.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <fcntl.h>

/* int	main(int ac, char **av)
{
	if (mkfifo("myfifo1", 0777) == -1)
	{
		if (errno != EEXIST)
		{
			printf("Could not create fifo file\n");
			return (1);
		}
	}
	printf("Opening...\n");
	int fd = open("myfifo1", O_RDWR);
	if (fd == -1)
		return (3);
	printf("Opened\n");
	int x = 97;
	if (write(fd, &x, sizeof(x)) == -1)
		{
			printf("Could not write to the file\n");
			return (2);
		}
	printf("Written\n");
	close (fd);
	printf("Closed\n");
	return (0);
} */


//to put 2children...

int	main(int ac, char **av)
{
	int arr[] = {1, 2, 3, 4, 1, 2, 7, 7};
	int	arrSize = sizeof(arr) / sizeof(int);
	int start, end;
	int fd[2];
	int id2;

	if (pipe(fd) == -1)
	{
		return (1);
	}
	int id = fork();
	if (id == -1)
	{
		return (2);
	}
	if (id == 0)
	{
		printf("id %d\n", getpid());
		printf("id %d\n", getppid());
	}
	else
	{
		id2 = fork();
		if (id2 == -1)
			return (5);
	}
	if (id == 0)
	{
		start = 0;
		end = start + arrSize / 2;
	}
	else if (id2 == 0)
	{
		printf("id %d\n", getpid());
		printf("id %d\n", getppid());
		start = 0;
		end = arrSize;
	}
	else
	{
		start = arrSize / 2;
		end = arrSize;
	}
	int sum = 0;
	int i;
	for(i = start; i < end; i++)
	{
		sum += arr[i];
	}

	printf("Calculated partial sum: %d in process %d\n", sum, getpid());

	if (id == 0)
	{
		close(fd[0]);
		if (write(fd[1], &sum, sizeof(sum)) == -1)
			return (3);
		close(fd[1]);
	}
	else if (id2 == 0)
	{
		close(fd[0]);
		sum++;
		if (write(fd[1], &sum, sizeof(sum)) == -1)
			return (3);
		close(fd[1]);
	}
	else
	{
		int sumFromChild = 0;
		int sumFromChild2 = 0;
		close(fd[1]);
		wait(NULL);
		if (read(fd[0], &sumFromChild, sizeof(sumFromChild)) == -1)
			return (4);
		if (read(fd[0], &sumFromChild2, sizeof(sumFromChild2)) == -1)
			return (4);
		close(fd[0]);
		int totalSume = sum + sumFromChild + sumFromChild2;
		printf("Total sum is %d\n", totalSume);
		wait(&id2);
	}


	return (0);
}

/* int	main(int ac, char **av)
{
	int arr[] = {1, 2, 3, 4, 1, 2};
	int arrSize = sizeof(arr) / sizeof(int);
	int start, end;
	int fd[2];
	if (pipe(fd) == -1)
	{
		return (1);
	}
	int id = fork();
	if (id == -1)
		return (2);
	if (id == 0)
	{
		start = 0;
		end = start + arrSize / 2;
	}
	else
	{
		start = arrSize / 2;
		end = arrSize;
	}

	int sum = 0;
	int i;
	for (i = start; i < end; i++)
	{
		sum += arr[i];
	}
	printf("Calculated partial sum: %d\n", sum);

	if (id == 0)
	{
		close(fd[0]);
		write(fd[1], &sum, sizeof(sum));
		close(fd[1]);
	}
	else
	{
		int sumFromChild;
		close(fd[1]);
		read(fd[0], sumFromChild, sizeof(sumFromChild));
	}


	return (0);
} */

/* int main(int ac, char **av)
{
	int fd[2];
//	fd[0] - read
//	fd[1] - write
	if (pipe(fd) == -1)
	{
		printf("Error with opening the pipe\n");
		return (1);
	}
	int id = fork();
	if (id == -1)
	{
		printf("Error with fork\n");
		return (4);
	}
	if (id == 0)
	{
		close(fd[0]);
		int x;
		printf("Input a number: ");	
		scanf("%d", &x);
		if (write(fd[1], &x, sizeof(int)) == -1)
		{
			printf("Error with write\n");
			return (2);
		}
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		int y;
		if (read(fd[0], &y, sizeof(int)) == -1)
		{
			printf("Error with read\n");
			return (3);			
		}
		y = y * 3;
		close(fd[0]);
		printf("Got from child process %d\n", y);
	}
	return (0);
}
 */
/* int	main(int ac, char **av)
{
	int	pids[PROCESS_NUM];
	int pipes[PROCESS_NUM + 1][2];
	int i;
	for (i = 0; i < PROCESS_NUM + 1; i++)
	{
		if (pipe(pipes[i]) == -1)
		{
			printf("Error with creating pipe\n");
			return (1);
		}
	}
	for (i = 0; i < PROCESS_NUM; i++)
	{
		pids[i] = fork();
		if (pids[i] == -1)
		{
			printf("Error with creating process\n");
			return (2);
		}
		if (pids[i] == 0)
		{
			//child process
			return (0);
		}
	}
	for (i = 0; i < PROCESS_NUM; i++)
	{
		wait(NULL);
	}

	return (0);
} */

/* int	main(int ac, char **av)
{
	int id1 = fork();
	int id2 = fork();
	if (id1 == 0)
	{
		if (id2 == 0)
		{
			printf("We are in process Y\n");
		}
		else
		{
			printf("We are in process X\n");
		}		
	}
	else
	{
		if (id2 == 0)
		{
			printf("We are in process Z\n");
		}
		else
			printf("We are in parent process\n");
	}
	while (wait(NULL) != -1 || errno != ECHILD)
	{
		printf("Waited for a child to finished\n");		
	}
	return (0);
} */

/* int	main(int ac, char **av)
{
	int	id = fork();
	if (id == 0)
	{
		sleep(1);
	}
	printf("Current ID: %d, parent ID: %d\n", getpid(), getppid());
	int res = wait(NULL);
	if (res == -1)
		printf("No children to wait for\n");
	else
	{
		printf("%d finished excution\n", res);
	}
	return (0);
} */

/* int	main(int ac, char **av)
{
	int id = fork();
	int n;
	int	time;
	if (id == 0)
	{
		n = 1;
	}
	else
	{
		n = 6;
	}
	if (id != 0)
	{
		wait(&time);
	}
	int i;
	for (i = n; i < n + 5; i++)
	{
		printf("%d ", i);
		fflush(stdout);
	}
	if (id != 0)
	{
		printf("\n");
	}

	return (0);
} */

/* int	main(int ac, char **av)
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
 */



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