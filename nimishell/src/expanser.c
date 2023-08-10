/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-mada <bde-mada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 09:49:30 by bde-mada          #+#    #+#             */
/*   Updated: 2023/06/19 09:49:30 by bde-mada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "minishell.h"
#include "../lib/libft/libft.h"
#include <stdio.h>

char	*get_var_value(char *env_var, int len, char *envp[])
{
	int	i;

	printf("\n\nenv var: %s, len: %d\n", env_var, len);
	i = -1;
	len--;
	while (envp[++i])
	{
		if (!ft_strncmp(env_var + 1, envp[i], len) && envp[i][len] == '=')
		{
			printf("pos of = : %c\n", envp[i][len]);
			return (ft_strdup(envp[i] + len + 1));
		}
	}
	return (ft_substr(env_var, 0, len));
}

char	*expand(char *arg, int start, int end, char *var_value)
{
	char	*expanded;
	char	*tmp;

	expanded = ft_substr(arg, 0, start);
	printf("First section: %s\n", expanded);
	tmp = expanded;
	expanded = ft_strjoin(expanded, var_value);
	printf("First section + expanded: %s\n", expanded);
	free(tmp);
	tmp = expanded;
	expanded = ft_strjoin(expanded, arg + end);
	free(tmp);
	printf("All: %s\n", expanded);
	return (expanded);
}

/**
 * pos[0] = where is '$'
 * pos[1] = the last letter of the word
  */
char	*expanser(char *arg, char *envp[])
{
	char	*expanded;
	char	*var_value;
	char	*tmp;
	int		i;
	int		pos[2];

	i = -1;
	expanded = ft_strdup(arg);
	while (expanded[++i])
	{
		if (expanded[i] == '$')
		{
			pos[0] = i;
			i++;
			while (ft_isalnum(arg[i]))
				i++;
			pos[1] = i;
			printf("start: %d, end: %d\n", pos[0], pos[1]);
			tmp = expanded;
			var_value = get_var_value(expanded + pos[0], pos[1] - pos[0], envp);
			printf("var value: %s\n", var_value);
			expanded = expand(expanded, pos[0], pos[1], var_value);
			i = i - (pos[1] - pos[0]) + ft_strlen(var_value) - 1; 
			printf("i val: %d, i pos after write: %s\n",i, arg + i);
			free(var_value);
			free (tmp);
		}
	}
	return (expanded);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*arg = "$SHELL first to expand SHELL, to expand 2 USER together: $USER$USER to expand HOME: $HOME, notexisting: $NONEXISTING";
	char	*expanded;
//	int		i = -1;

	expanded = NULL;
	if (argc != 1 && !*argv)
		return (1);
// 	while (envp[++i])
//		printf("%s\n", envp[i]);
//	printf("\n\n");
// 	expanded = get_var_value("USER", 4, envp);
	expanded = expanser(arg, envp);
	printf("expanded str: %s\n", expanded); 
	free (expanded);
	return (0);
}

//消していいと思う
