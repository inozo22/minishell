#include <stdio.h>
#include <string>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include "mypipe.h"

t_pine	*init_pine(t_pine *pine)
{
	t_pine	*tmp;

	tmp = (t_pine *)mem_malloc_log(sizeof(t_pine));
	if (!tmp)
		return (NULL);
	tmp->mark = 0;
	return (tmp);
}

int	main(int ac, char **av)
{
	int		i;
	int		j;
	t_pine	*pine;

	pine = NULL;
	pine = init_pine(pine);
	pine->mem = NULL;
	pine->mem = mem_init(pine->mem);
	i = 1;
	j = 0;
	while (av[i])
	{
		while (av[i][j])
		{
			if (av[i][j] == 34 || av[i][j] == 39)
			{
				pine->mark = av[i][j];
				j++;
				while (av[i][j] && av[i][j] != pine->mark)
				{
					
					j++;
				}
				if (av[i][j] != pine->mark)
			}
			j++;
		}


		i++;
	}
	mem_check(pine->mem);
	return (0);
}
