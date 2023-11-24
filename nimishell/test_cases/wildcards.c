/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-mada <bde-mada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 18:57:34 by bde-mada          #+#    #+#             */
/*   Updated: 2023/09/07 15:27:56 by bde-mada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <dirent.h>
#include <errno.h>
//#include "../lib/libft/libft.h"
#include "../include/minishell.h"

#define BLUE "\033[1;34m"
#define YELLOW "\033[1;33m"
#define RED "\033[1;31m"
#define CYAN "\033[1;36m"
#define GREEN "\033[1;32m"
#define CLEAR "\033[0m"

int	obtain_counter(char *input)
{
	int	i;
	int	ret;

	i = -1;
	ret = 0;
	while (input[++i])
	{
		if (input[i] != '*')
			ret++;
	}
	return (ret);
}

int	*check_input_tab(char *input, char **tab, char *dirname, int *i)
{
	if (ft_strlen(tab[i[4]]) == 1)
	{
		if (tab[i[4]][0] == dirname[i[1]])
		{
			i[3]++;
			i[0]++;
			i[1]++;
			i[4]++;
		}
	}
	else if (ft_strncmp(tab[i[4]], &dirname[i[1]], ft_strlen(tab[i[4]])) == 0)
	{
		i[3] += (int)ft_strlen(tab[i[4]]);
		i[0] += i[3] - 1;
		i[1] += i[3] - 1;
		i[4]++;
		if (!tab[i[4]] && ((i[1] >= (int)ft_strlen(dirname)) || \
		(i[3] == i[2] && ((input[ft_strlen(input) - 1] == '*') || \
		(!input[++i[0]] && !dirname[++i[1]])))))
			i[5] = 1;
	}
	else
		i[1]++;
	return (i);
}

/**
 * @brief to free ** array
 * @note I couldn't find where is, it should be replaced (if there is)
 * 
  */
void	myfree_array(char **tab)
{
	int	i;

	i = 0;
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
	// int		flag; i[5]
int	valid_wildcard(char *input, char *dirname)
{
	int		*i;
	char	**tab;

	i = ft_calloc(6, sizeof(int));
	if (!i)
		return (0);
	i[2] = obtain_counter(input);
	tab = ft_split(input, '*');
	while (input[i[0]] && input[i[0]] == '*')
		i[0]++;
	while (dirname[i[1]] && input[i[0]] && i[1] < (int)ft_strlen(dirname))
	{
		if (input[i[0] - 1] == '*')
		{
			while (dirname[i[1]] && (input[i[0]] != dirname[i[1]]))
				i[1]++;
		}
		i = check_input_tab(input, tab, dirname, i);
		if (i[5] == 1)
			return (myfree_array(tab), free (i), 1);
		while (input[i[0]] && input[i[0]] == '*')
			i[0]++;
	}
	return (myfree_array(tab), free (i), 0);
}

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

int	main(int argc, char **argv)
{
//	printf("Line: %d\n", __LINE__);
	if (argc != 2)
		return (0);
	wildcards(argv[1]);
	printf("\n*******-----********	👻	*******-----********\n");
	printf("\n*******-----********	👻	*******-----********\n");
	wildcards("*s*he*****ll*");
//	printf("Line: %d\n", __LINE__);
	system ("leaks minishell");
	return 0;
}
