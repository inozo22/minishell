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

char	*get_var_value(char *env_var, char *envp[])
{
	int	i;
	int	len;

	printf("\n\nenv var: %s\n", env_var);
	i = -1;
	len = ft_strlen(env_var);
	while (envp[++i])
	{
		printf("pos of = : %c\n", envp[i][len]);
		if (!ft_strncmp(env_var + 1, envp[i], len) && envp[i][len] == '=')
			return (ft_strdup(envp[i] + len + 1));
	}
	return (ft_substr(env_var, 0, len));
}
//$- returns a string representing the flags of the shell
//$@ $< and $> not implemented, return empty
/**
 * @brief expands considering the special parameters in bash
 * @author bde-mada
 * @note ($*) Expands to the positional parameters, starting from one.
 * @note ($@) Expands to the positional parameters, starting from one.
 * @note ($#) Expands to the number of positional parameters in decimal.
 * @note ($?) Expands to the exit status of the most recently executed 
 * foreground pipeline.
 * @note ($-) Expands to the current option flags as specified upon invocation,
 * by the set builtin command, or those set by the shell itself.
 * @note ($$) Expands to the process ID of the shell. In a subshell, it expands
 * to the process ID of the invoking shell, not the subshell.
 * @note ($!) Expands to the process ID of the job most recently placed into
 * the background
 * @note ($0) Expands to the name of the shell or shell script.
 * @note ($$) Expands to the pid of the current shell.
 * @note ($1-9) Expands to the corresponding arguments passed to bash
 */
char	*is_expand(char *token, char *envp[])
{
/* 	int	i;

	i = -1; */
	if (ft_strncmp(token, "$?", 2))
		return (/* data->return_val */"1");
	if (ft_strncmp(token, "$!", 2))
		return (/* data->return_val */"1000");
	if (ft_strncmp(token, "$$", 2))
		return (/* ft_itoa(data->pid) */"1000");
	if (ft_strncmp(token, "$-", 2))
		return ("himBH");
	if (ft_strncmp(token, "$@", 2) || ft_strncmp(token, "$*", 2))
		return ("");
	if (ft_strncmp(token, "$#", 2))
		return ("0");
	if (ft_strncmp(token, "$IFS", 4))
		return ("\t\n");
	if (ft_isdigit(token[1]))
		return ("");
	if (!(token[1]) || (!ft_isalnum(token[1]) && token[1] != '_'))
		return (NULL);
	return(get_var_value(token, envp));
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



char	*expanser(char *arg, char *envp[])
{
	char	*expanded;
	char	*var_value;
	char	*tmp;
	int		i;
	char 	*pos[2];

	i = -1;
	expanded = ft_strdup(arg);
	pos[0] = ft_strchr(expanded, '$');
	while (pos[0])
	{
		pos[1] = pos[0] + 1;
		while (ft_isalnum(*pos[1]))
			pos[1]++;
		printf("start: %s, end: %s\n", pos[0], pos[1]);
		tmp = expanded;
		var_value = is_expand(pos[0], envp);
		printf("var value: %s\n", var_value);
		expanded = expand(expanded, pos[0] - expanded, pos[1] - pos[0], var_value);
		printf("i val: %d, i pos after write: %s\n",i, arg + i);
		free(var_value);
		free (tmp);
	}
	return (expanded);
}

/* int	main(int argc, char *argv[], char *envp[])
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
 */
