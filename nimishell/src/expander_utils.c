/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 18:46:11 by nimai             #+#    #+#             */
/*   Updated: 2023/09/19 18:53:14 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//DELETE
//#include "../lib/libft/libft.h"

//volatile int	g_return_val = 0;

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

/* char	*obtain_expanded(char *tmp, char *ret, char *arg)
{
	if (ft_strcmp(ret, arg) != 0)
		ret = ft_strjoin(ret, tmp);
	else
	{
		free (ret);
		ret = ft_calloc(ft_strlen(tmp), 1);
		ft_strcpy(ret, tmp);
	}
	return (ret);
} */

/**
 * @note i[0] i
 * @note i[1] j
 * @note i[2] len
  */
char	*remove_quotes(char *str)
{
	char	*ret;
	int		i[3];

	ft_bzero(i, 3 * sizeof(int));
	ret = NULL;
	while (str[i[0]])
	{
		if (str[i[0]] != '\'' && str[i[0]] != '\"')
			i[2]++;
		i[0]++;
	}
	ret = ft_calloc(i[2] + 1, sizeof(char));
	if (!ret)
		return (NULL);
	while (--i[0] > -1)
	{
		if (str[i[0]] != '\'' && str[i[0]] != '\"')
			ret[--i[2]] = str[i[0]];
	}
	free(str);
	return (ret);
}

