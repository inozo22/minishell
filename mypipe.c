#include <stdio.h>
#include <string>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int	main(int ac, char **av)
{
	int	i;
	int j;

	i = 1;
	j = 0;
	while (av[i])
	{
		if (av[i][j] == 34)
		while (av[i][j])
		{

			j++;
		}
		i++;
	}

	return (0);
}
