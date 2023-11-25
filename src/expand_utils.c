/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:20:01 by nimai             #+#    #+#             */
/*   Updated: 2023/10/02 16:27:58 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var_value(char *env_var, char *envp[], int len)
{
	int	i;
	int	pos;

	pos = 0;
	while (env_var[pos] != '$' && env_var[pos])
		pos++;
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
	if (!ft_strncmp(env_var, "$!", 2))//it should return process ID of the job most recently placed into the background, now, return last return value
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
		return (ft_strdup(SH_NAME));
	if (!ft_strncmp(env_var, "$IFS", 4))
		return (ft_strdup("\t\n"));
	if (!ft_strncmp(env_var, "$\0", 2) || !ft_strncmp(env_var, "$\"", 2))
		return (ft_strdup("$"));
	if (ft_isdigit(env_var[1]))
		return (ft_strdup(""));
	if (!(env_var[1]) || (!ft_isalnum(env_var[1]) && env_var[1] != '_') || !ft_strncmp(env_var, "$ ", 2))
		return (ft_substr(env_var, 0, 2));//should be printed literally instead of null
	return (get_var_value(env_var + 1, env, len - 1));
}

int	compose_expanded(char *expanded, char **str, int start, int end)
{
	char	*preceding;
	char	*following;
	int		len;
	char	*tmp;

	tmp = *str;
	preceding = ft_substr(*str, 0, start);
	if (!preceding)
		return (0);
	following = ft_substr(*str, end, ft_strlen(*str) - end);
	if (!following)
		return (free(preceding), -9);
	if (!expanded)
		*str = ft_strjoin(preceding, following);
	else
		*str = ft_strjoin_many(3, preceding, expanded, following);
	free (tmp);
	if (!(*str))
		return (free(preceding), free(following), -9);
	len = expanded_len(expanded, preceding, following);
	return (free(preceding), free(following), free(expanded), len);
}

/**
 * @return 1 when there is only '$'
 * @return 2 when there are '$' and sth will not be a variable such as '%'
 */
int	is_special_expand(char *str, int ret)
{
	if (str[1] == '?' || str[1] == '!' || str[1] == '$' || \
	str[1] == '-' || str[1] == '@' || str[1] == '*' || str[1] == '#' || \
	str[1] == '0')
		return (ret + 1);
	if (ft_isdigit(str[ret]))
		return (ret + 1);
	if (!str[ret] || str[ret] == '\"')
		return (ret);
	if (!ft_strncmp(str, "IFS", 3))
		return (ret + 3);
	if (ft_isspace(str[ret]) || (!ft_isalnum(str[ret]) && str[ret] != '_'))
		return (ret + 1);
	return (0);
}

/**
 * @note ret  always start with '$', so skip it and the start from 1
 */
int	check_valiable_len(char *str, int start, int quotes)
{
	int	ret;

	ret = 1;
	ret = is_special_expand(str, ret);
	if (ret)
		return (start + ret);
	while (str[++ret])
	{
		if (!str[ret] || str[ret] == quotes || ft_isspace(str[ret]) || \
		(!ft_isalnum(str[ret]) && str[ret] != '_'))
			break ;
	}
	return (start + ret);
}
