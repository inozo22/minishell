/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanser2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 10:32:20 by nimai             #+#    #+#             */
/*   Updated: 2023/08/10 10:32:20 by nimai            ###   ########.fr       */
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

int	compose_expanded(char *expanded, char **str, int dollar_pos, int end_pos)
{
	char	*preceding;
	char	*following;
	int		len;

	preceding = ft_substr(*str, 0, dollar_pos);
	if (!preceding)
		return (0);
	following = ft_substr(*str, end_pos, ft_strlen(*str) - end_pos);
	if (!following)
		return (free(preceding), -9);
	if (!expanded)
		*str = ft_strjoin(preceding, following);
	else
		*str = ft_strjoin_many(3, preceding, expanded, following);
	if (!(*str))
		return (free(preceding), free(following), -9);
	len = expanded_len(expanded, preceding, following);
	return (free(preceding), free(following), free(expanded), len);
}

/**
 * @note pieces[0] before $
 * @note pieces[1] expanded var
 * @note pieces[2] after var 
 */
int	expand(char **str, int *pos, int quotes, char **env, pid_t pid)
{
	int		i[2];
	char	*expanded_var;

	expanded_var = NULL;
	ft_bzero(i, 2 * sizeof(int));
	i[0] = *pos;
	if (!ft_isdigit((*str)[*pos]))
	{
		if ((*str)[i[0]] && !ft_isspace((*str)[i[0]]) && (*str)[i[0]] != quotes)
			i[0]++;
		while ((*str)[i[0]] && !ft_isspace((*str)[i[0]]) && (*str)[i[0]] != quotes\
		 && (*str)[i[0]] != '$' && (*str)[i[0]] != '\'' && (*str)[i[0]] != '\"')
			i[0]++;
		if (ft_strncmp(&(*str)[*pos], "$$", 2) == 0)
			i[0]++;
	}
	expanded_var = is_expand(&(*str)[*pos], i[0] - *pos, env, pid);
	*pos = compose_expanded(expanded_var, str, *pos, i[0]);
	if (*pos == -9)//230919nimai: changed error number to use -1 as length
		return (1);
//	is_quote(quotes);
	if (!(*str))
		return (1);
	return (0);
}

/**
 * @param pos[2] to keep and free string 
 */
char	*expander(char *str, char *env[], pid_t pid)
{
	int		i;
	int		c;
	int		quotes;
	char	**tab;
	char	*ret;

	tab = split_quotes(str);
	c = -1;
	while (tab[++c])
	{
		i = -1;
		while (tab[c][++i])
		{
			quotes = is_quote(tab[c][i]);
			if (tab[c][i] == '$' && quotes != '\'')
			{
				if (expand(&tab[c], &i, quotes, env, pid))
					return (NULL);
			}
		}
		if (tab[c][0] == '\'' || tab[c][0] == '\"')
			tab[c] = remove_quotes(tab[c]);
		if (c == 0)
			ret = ft_strdup(tab[c]);
		else
			ret = ft_strjoin(ret, tab[c]);
	}
	return (strs_free(tab), ret);
}
