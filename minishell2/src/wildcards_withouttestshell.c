/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 18:57:34 by bde-mada          #+#    #+#             */
/*   Updated: 2023/07/20 10:33:36 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <dirent.h>
#include <errno.h>
//#include "../lib/libft/libft.h"
#include "minishell.h"

#define BLUE "\033[1;34m"
#define YELLOW "\033[1;33m"
#define RED "\033[1;31m"
#define CYAN "\033[1;36m"
#define GREEN "\033[1;32m"
#define CLEAR "\033[0m"

int	valid_wildcard(char *input, char *dirname, int pos)
{
	int check;
	int	i;
	int	j;
	int	counter;
	int	k;
//	char	**tab;

	check = 0;
	i = -1;
	j = 0;
	k = 0;
	counter = 0;
	if (!ft_strncmp(input, dirname, pos))
		check = 1;
	while (input[++i])
	{
		if (input[i] != '*')
			counter++;
	}
/* 	tab = ft_split(input, '*');
	while (tab)
	{
		printf("tab: %s\n", *tab);
		tab++;
	}
	exit(0); */
//	printf("counter: %d\n", counter);
	i = 0;
	while (dirname[j])
	{
//		printf("Line: %d input: %c dirname: %c\n", __LINE__, input[i], dirname[j]);
		while (input[i] == '*')
			i++;
//		printf("Line: %d input: %c dirname: %c\n", __LINE__, input[i], dirname[j]);
		if (input[i - 1] == '*')
		{
			while (input[i] && input[i] != '*')
			{
//				printf("Line: %d input: %c dirname: %c\n", __LINE__, input[i], dirname[j]);
				while (dirname[j] && (input[i] != dirname[j]))
					j++;
//				printf("Line: %d input: %c dirname: %c\n", __LINE__, input[i], dirname[j]);
				while (input[i] && dirname[j] && input[i] == dirname[j])
				{
					i++;
					j++;
					k++;
//					printf("Line: %d input: %c dirname: %c k: %d\n", __LINE__, input[i], dirname[j], k);
				}
				i++;
			}
		}
//		printf("Line: %d input: %c dirname: %c\n", __LINE__, input[i], dirname[j]);

//		if (input[i] == '\0' && dirname[j] == '\0' || input[i] == '*' && input[i + 1] == '\0')
//			return (1);
//		printf("Line: %d input: %c dirname: %c\n", __LINE__, input[i], dirname[j]);
//		while (input[i] == '*')
//			i++;
		j++;
	}
//	printf("counter: %d k: %d\n", counter, k);
	if (dirname[j] == '\0' && k == counter)
		check = 1;
//	printf("check: %d\n", check);
	return (check);
}

/* int	valid_wildcard(char *entry, char *wildcard, int pos)
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
//	if (ft_strncmp(entry + ft_strlen(entry) - (ft_strlen(wildcard) - pos) + 1, wildcard + pos + 1, ft_strlen(wildcard + pos + 1)))
//		check = 0;
	while (wildcard[j])
	{
		printf("Line: %d entry: %c wildcard: %c\n", __LINE__, entry[i], wildcard[j]);
		while (entry[i] == '*')
			i++;
		if (entry[i - 1] == '*')
		{
			printf("Line: %d entry: %c wildcard: %c\n", __LINE__, entry[i], wildcard[j]);
			while (wildcard[j] && (entry[i] != wildcard[j]))
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
//		while (entry[i] == '*')
//			i++;
		j++;
	}
	return (check);
} */

char	*wildcards(char *str)
{
	DIR				*directory;
	struct dirent	*entry;
	int				pos;

	pos = (int)ft_strchr(str, '*');
	directory = opendir(".");
	if (directory != NULL)
	{
		while ((entry = readdir(directory)) != NULL)
		{
			if (entry->d_name[0] != '.')
			{
				printf("\n%s%s%s\n", YELLOW, entry->d_name, CLEAR);
				if (valid_wildcard(str, entry->d_name, pos))
				{
					printf("%smatch%s\n\n", RED, CLEAR);
				}
			}
		}
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
//	printf("Line: %d\n", __LINE__);
	wildcards("*she*ll*******");
//	printf("Line: %d\n", __LINE__);
	return 0;
}
