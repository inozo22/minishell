#include <sys/stat.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
		struct stat t_stat;
		
		int ret = stat(argv[1], &t_stat);
		printf("ret: %d\n", ret);
		printf("S_ISDIR(t_stat.st_mode): %d\n", S_ISDIR(t_stat.st_mode));
		if (ret && S_ISDIR(t_stat.st_mode))
			return (1);
		return (0);
}