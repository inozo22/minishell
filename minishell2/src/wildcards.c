/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 18:57:34 by bde-mada          #+#    #+#             */
/*   Updated: 2023/07/19 15:53:55 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include "../lib/libft/libft.h"

#define BLUE "\033[1;34m"
#define YELLOW "\033[1;33m"
#define RED "\033[1;31m"
#define CYAN "\033[1;36m"
#define GREEN "\033[1;32m"
#define CLEAR "\033[0m"

int	valid_wildcard(char *entry, char *wildcard, int pos)
{
	int check;
	int	i;
	int	j;

	check = 0;
	i = 0;
	j = 0;
//	printf("Line: %d entry: %s wildcard: %s\n", __LINE__, entry, wildcard);
	if (!ft_strncmp(entry, wildcard, pos))
		check = 1;
/* 	if (ft_strncmp(entry + ft_strlen(entry) - (ft_strlen(wildcard) - pos) + 1, wildcard + pos + 1, ft_strlen(wildcard + pos + 1)))
		check = 0; */
	while (wildcard[j] && entry[i])
	{
		printf("Line: %d entry: %c wildcard: %c\n", __LINE__, entry[i], wildcard[j]);
		while (entry[i] == '*')
			i++;
		if (entry[i - 1] == '*')
		{
			printf("Line: %d entry: %c wildcard: %c\n", __LINE__, entry[i], wildcard[j]);
			while (wildcard[j] && entry[i] != wildcard[j])
				j++;
		}
		while (entry[i] && wildcard[j] && entry[i] == wildcard[j])
		{
			i++;
			j++;
		}
		if (entry[i] == '\0' && wildcard[j] == '\0' || entry[i] == '*' && entry[i + 1] == '\0')
			return (1);
		printf("Line: %d entry: %c wildcard: %c\n", __LINE__, entry[i], wildcard[j]);
/* 		while (entry[i] == '*')
			i++; */
		j++;
	}
	return (check);
}

char	*wildcards(char *str)
{
	DIR				*directory;
	struct dirent	*entry;
	int				pos;

	pos = ft_strchr(str, '*');
	directory = opendir(".");
	if (directory != NULL)
	{
		while ((entry = readdir(directory)) != NULL)
		{
//			printf("Line: %d\n", __LINE__);
			if (entry->d_name[0] != '.')
			{
				printf("%s%s%s\n", CYAN, entry->d_name, CLEAR);
				if (valid_wildcard(str, entry->d_name, pos))
				{
					printf("%smatch%s\n", RED, CLEAR);
				}
			}
		}
//		printf("Line: %d\n", __LINE__);
		closedir(directory);
	}
	else
	{
		printf("opendir: ");
		strerror(errno);
	}
	return (str);
}

int	main()
{
	printf("Line: %d\n", __LINE__);
	wildcards("*she*******ll*");
//	printf("Line: %d\n", __LINE__);
	return 0;
}
