/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 18:57:34 by bde-mada          #+#    #+#             */
/*   Updated: 2023/07/21 10:07:26 by nimai            ###   ########.fr       */
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

/* int	*check_input_tab(char *input, char **tab, char *dirname, int *i)
{
	




	return (i);
} */

/**
 * @brief to free ** array
 * @note I couldn't find where is, it should be replaced (if there is)
 * 
  */
void	myfree_array(char **tab)
{
	int	i;

	i = 0;
	printf("tab[0]: %s\n", tab[i]);
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
}

	// int		i;	i[0]
	// int		j;	i[1]
	// int		counter;	i[2]
	// char	**tab;
	// int		ret;	i[3]
	// int		t;	i[4]
int	valid_wildcard(char *input, char *dirname)
{
	int		*i;
	char	**tab;
	// int		t;

	i = ft_calloc(5, sizeof(int));
	//count how many letters there are
	while (input[++i[0]])
	{
		if (input[i[0]] != '*')
			i[2]++;
	}
	tab = ft_split(input, '*');
	// t = 0;
	i[0] = 0;
	printf("Line. %d\n", __LINE__);
	while (input[i[0]] && input[i[0]] == '*')
		i[0]++;
	while (dirname[i[1]] && input[i[0]] && i[1] < (int)ft_strlen(dirname))
	{
		if (input[i[0] - 1] == '*')
		{
			while (dirname[i[1]] && (input[i[0]] != dirname[i[1]]))
				i[1]++;
		}
		printf("Line: %d\n", __LINE__);
//		i = check_input_tab(input, tab, dirname, i);
		if (ft_strlen(tab[i[4]]) == 1)
		{
			printf("Line: %d\n", __LINE__);
			if (tab[i[4]][0] == dirname[i[1]])
			{
				i[3]++;
				i[0]++;
				i[1]++;
				i[4]++;
			}
		}
		else if (ft_strncmp(tab[i[4]], &dirname[i[1]], (int)ft_strlen(*tab)) == 0)
		{
			printf("Line: %d\n", __LINE__);
			i[3] += ft_strlen(*tab);
			printf("Line: %d\n", __LINE__);
			i[0] += i[3] - 1;
			i[1] += i[3] - 1;
			printf("Line: %d\n", __LINE__);
			i[4]++;
			printf("Line: %d\n", __LINE__);
			if (!tab[i[4]] && ((i[1] >= (int)ft_strlen(dirname)) || (i[3] == i[2] && input[i[0] + 1] == '*')))
			{
				printf("Line: %d\n", __LINE__);
				//myfree_array(tab);
				printf("Line: %d\n", __LINE__);
				return (1);
			}
			else if (!tab[i[4]])
			{
				printf("Line: %d\n", __LINE__);
				break ;
			}
		}
		else
			i[1]++;
		printf("Line: %d\n", __LINE__);
		while (input[i[0]] && input[i[0]] == '*')
			i[0]++;
	}
	if (((input[ft_strlen(input) - 1] == '*' && dirname[++i[1]]) || (!input[++i[0]] && !dirname[++i[1]])) && i[3] == i[2])
		return (/* myfree_array(tab) ,*/ 1);
	return (/* myfree_array(tab),  */0);
}

//		printf("Line: %d	input: %s dirname: %s\n", __LINE__, &input[i], &dirname[j]);

	// printf("Line: %d	i: %d j: %d\n", __LINE__, i, j);
	// printf("Line: %d	ret: %d counter: %d\n", __LINE__, ret, counter);
	// printf("Line: %d	input: %s dirname: %s\n", __LINE__, &input[i], &dirname[j]);




/* int	valid_wildcard(char *input, char *dirname)
{
	int check;
	int	i;
	int	j;
	int	counter;
	int c;
	char	**tab;

	check = 0;
	i = -1;
	j = 0;
	counter = 0;
//	if (!ft_strncmp(input, dirname, pos))
//		return (1);
	while (input[++i])
	{
		if (input[i] != '*')
			counter++;
	}
	tab = ft_split(input, '*');
	while (tab[j])
	{
		printf("tab: %s\n", tab[j]);
		j++;
	}
	j = 0;
	i = 0;
	c = 0;
	while (dirname[j])
	{
		while (input[i] && input[i] == '*')
			i++;
		while (input[i] && input[i] != '*')
		{
			if (input[i - 1] == '*')
			{
				while (dirname[j] && (input[i] != dirname[j]))
					j++;
			}
			if (ft_strlen(tab[c]) == 1)
			{
				printf("tab[%d]: %s dirname[%d]: %c &input[%d]: %s\n", c, tab[c], j, dirname[j], i, &input[i]);
				if (tab[c][0] == dirname[j])
				{
					check++;
					i++;
					j++;
					c++;
				}
			}
			else if (ft_strncmp(tab[c], &dirname[j], ft_strlen(tab[c])) == 0)
			{
				check += ft_strlen(tab[c]);
				i += check;
				j += check;
				c++;
				printf("tab[%d]: %s dirname[%d]: %c &input[%d]: %s\n", c, tab[c], j, dirname[j], i, &input[i]);
				if (!tab[c] && !dirname[j])
					return (1);
			}
			if (!tab[c] && &dirname[j] && input[++i] == '*')
			{
				printf("check every parts\n");
				return (1);
			}
			else if (dirname[j] && (input[i] == dirname[j]))
				j++;
			else
				i++;
		}
		j++;
	}
	if (dirname[j] == '\0' && check == counter)
		check = 1;
	else
		check = 0;
	return (check);
} */

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
				if (valid_wildcard(str, entry->d_name))
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
	wildcards("*.out");
	printf("\n*******-----********	👻	*******-----********\n");
	printf("\n*******-----********	👻	*******-----********\n");
	wildcards("*s*he*****ll*");
//	printf("Line: %d\n", __LINE__);
//	system ("leaks minishell");
	return 0;
}
