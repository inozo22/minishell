/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 18:46:11 by nimai             #+#    #+#             */
/*   Updated: 2023/09/20 17:36:21 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var_value(char *env_var, char *envp[], int len)
{
	int	i;
	int	pos;

	pos = 0;
	while (env_var[pos] != '$' && env_var[pos])
	{
		pos++;
	}
	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(env_var, envp[i], len) && envp[i][len] == '=')
			return (ft_strdup(envp[i] + len + 1));
	}
	return (NULL);
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
 * @note 230919nimai: ($\0) It's not expantion, but only this case receive single '$'
 */
char	*is_expand(char *env_var, int len, char *env[], pid_t pid)
{
	printf("env_var: %s\n", env_var);
	if (!ft_strncmp(env_var, "$?", 2))
		return (ft_itoa(g_return_val));
	if (!ft_strncmp(env_var, "$!", 2))
		return (ft_itoa(g_return_val));
	if (!ft_strncmp(env_var, "$$", 2))
		return (ft_itoa(pid));
	if (!ft_strncmp(env_var, "$-", 2))
		return (ft_strdup("himBH"));
	if (!ft_strncmp(env_var, "$@", 2) || !ft_strncmp(env_var, "$*", 2))
		return (ft_strdup(""));
	if (!ft_strncmp(env_var, "$#", 2))
		return (ft_itoa(0));
	if (!ft_strncmp(env_var, "$0", 2))
		return (ft_strdup(SHELL_NAME));
	if (!ft_strncmp(env_var, "$IFS", 4))
		return (ft_strdup("\t\n"));
	if (!ft_strncmp(env_var, "$\0", 2))
		return (ft_strdup("$"));
	if (ft_isdigit(env_var[1]))
		return (ft_strdup(""));
	if (!(env_var[1]) || (!ft_isalnum(env_var[1]) && env_var[1] != '_'))
		return (NULL);
	return (get_var_value(env_var + 1, env, len - 1));
}

// char	*remove_quotes(char *str)
// {
// 	char	*ret;
// 	int		i[3];
// //	int		quotes;

// 	ft_bzero(i, 3 * sizeof(int));
// 	ret = NULL;
// //	quotes = str[0];
// 	if (str[i[0]] != '\"' && str[i[0]] != '\'')
// 		return (str);
// 	while (str[i[0]])
// 	{
// 		if (str[i[0]] != '\'' || str[i[0]] != '\"')
// 			i[2]++;
// 		i[0]++;
// 	}
// 	ret = ft_calloc(i[2] + 1, sizeof(char));
// 	if (!ret)
// 		return (NULL);
// 	while (--i[0] > -1)
// 	{
// 		if (str[i[0]] != '\'' || str[i[0]] != '\"')
// 			ret[--i[2]] = str[i[0]];
// 	}
// 	free(str);
// 	return (ret);
// }


char	*remove_quotes(char *str, int quotes)
{
	char		*ret;
	int			i[4];
//	int			quotes;

	printf("check quotes in removing: %c\n", quotes);
	ft_bzero(i, 4 * sizeof(int));
	ret = NULL;
//	quotes = str[0];
	// if (quotes != '\"' && quotes != '\'')
	// 	return (str);
	while (str[i[0]])
	{
		if (str[i[0]] != quotes)
			i[2]++;//len
		else
			break ;
		i[0]++;
	}
	while (str[i[0]])
	{
		i[0]++;
		i[2]++;
	}
	printf("i[2]: %d\n", i[2]);
	ret = ft_calloc(i[2] + 1, sizeof(char));
	if (!ret)
		return (NULL);
	i[0] = -1;
	while (++i[0] < i[2]/* --i[0] > -1   */&& str[i[0]])
	{
		if (str[i[0]] != quotes)
			ret[i[1]] = str[i[0]];
		else
			break ;
		i[1]++;
	}
	if (str[i[0]])
		i[0]++;
	while (i[0] < i[2])
	{
		ret[i[1]++] = str[i[0]++];
	}
	printf("str: %s ret: %s\n", str, ret);
	free(str);
	return (ret);
}

// char	*remove_quotes(char *str)
// {
// 	char		*ret;
// 	int			i[3];
// 	int			quotes;

// 	ft_bzero(i, 3 * sizeof(int));
// 	ret = NULL;
// 	quotes = str[0];
// 	if (quotes != '\"' && quotes != '\'')
// 		return (str);
// 	while (str[i[0]])
// 	{
// 		if (str[i[0]] != quotes)
// 			i[2]++;
// 		i[0]++;
// 	}
// 	ret = ft_calloc(i[2] + 1, sizeof(char));
// 	if (!ret)
// 		return (NULL);
// 	while (--i[0] > -1)
// 	{
// 		if (str[i[0]] != quotes)
// 			ret[--i[2]] = str[i[0]];
// 	}
// 	free(str);
// 	return (ret);
// }

