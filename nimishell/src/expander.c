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

//DELETE
//#include "../lib/libft/libft.h"

//volatile int	g_return_val = 0;

char	*get_var_value(char *env_var, char *envp[], int len)
{
	int	i;

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
 */
char	*is_expand(char *env_var, int len, char *env[], pid_t pid)
{
	if (!ft_strncmp(env_var, "$?", len))
		return (ft_itoa(g_return_val));
	if (!ft_strncmp(env_var, "$!", len))
		return (ft_itoa(g_return_val));
	if (!ft_strncmp(env_var, "$$", len))
		return (ft_itoa(pid));
	if (!ft_strncmp(env_var, "$-", len))
		return (ft_strdup("himBH"));
	if (!ft_strncmp(env_var, "$@", len) || !ft_strncmp(env_var, "$*", len))
		return (ft_strdup(""));
	if (!ft_strncmp(env_var, "$#", len))
		return (ft_itoa(0));
	if (!ft_strncmp(env_var, "$0", len))
		return (ft_strdup(SHELL_NAME));
	if (!ft_strncmp(env_var, "$IFS", len))
		return (ft_strdup("\t\n"));
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

int	compose_expanded(char *expanded, char **str, int dollar_pos, int end_pos)
{
	char	*preceding;
	char	*following;
	int		len;

	preceding = ft_substr(*str, 0, dollar_pos);
	if (!preceding)
		return (0);
	preceding = remove_quotes(preceding);
	following = ft_substr(*str, end_pos, ft_strlen(*str) - end_pos);
	if (!following)
		return (free(preceding), -1);
	following = remove_quotes(following);
	if (!expanded)
		*str = ft_strjoin(preceding, following);
	else
		*str = ft_strjoin_many(3, preceding, expanded, following);
	if (!(*str))
		return (free(preceding), free(following), -1);
	if (expanded)
		len = ft_strlen(preceding) + ft_strlen(expanded) - 1;
	else
		len = ft_strlen(preceding) - 1;
	free(preceding);
	free(following);
	free(expanded);
	return (len);
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

	ft_bzero(i, 2 * sizeof(int));
	i[0] = *pos;
	if (!ft_isdigit((*str)[*pos]))
		while ((*str)[i[0]] && !ft_isspace((*str)[i[0]]) \
					&& (*str)[i[0]] != quotes)
			i[0]++;
	expanded_var = is_expand(&(*str)[*pos], i[0] - *pos, env, pid);
	*pos = compose_expanded(expanded_var, str, *pos, i[0]);
	if (*pos == -1)
		return (1);
	is_quote(quotes);
	if (!(*str))
		return (1);
	return (0);
}

/**
 * @param pos[2] to keep and free string 
 */
char	*expander(char *str, char *env[], pid_t pid)
{
	int	i;
	int	quotes;

	i = -1;
	while (str[++i])
	{
		quotes = is_quote(str[i]);
		if (str[i] == '$' && quotes != '\'')
			if (expand(&str, &i, quotes, env, pid))
				return (NULL);
	}
	return (str);
}

/* int	main(int argc, char *argv[], char *envp[])
{
	char	*input[] = {"'$HOME': $HOME aaa", "   '$USER':  \"$USER\"$USER ei", "'$PWD':\"$PWD\"", "'$OLDPWD':\"$OLDPWD\"", "\"$USER\"", "'$INVENT':\"$INVENT\"", "'$?'\"$?\"", "'$-':\"$-\"",
			"'$0':\"$0\"", "'$1':\"$1\"", "'$USER$HOME':$USER$HOME", NULL};
	char	*str;
	char	*expanded;
	int		i = -1;

	if (argc != 1 || !argv || !envp)
		return (1);
	while (input[++i])
	{
		ft_printf("Expanding %s\n", input[i]);
		str = ft_strdup(input[i]);
		expanded = expander(str, envp, 123);
		printf("expanded: %s\n\n", expanded);
		free(expanded);
	}
	return (0);
} */

// cc -Wall -Wextra -g3 -fsanitize=address -Ilib/libft -Iinclude src/expander.c
// src/lexer.c src/error_msgs.c src/terminate.c lib/libft/libft.a && ./a.out

// cc -Wall -Wextra -g3 -Ilib/libft -Iinclude src/expander.c src/lexer.c
// src/error_msgs.c src/terminate.c lib/libft/libft.a && valgrind
// --leak-check=full --show-leak-kinds=all ./a.out
