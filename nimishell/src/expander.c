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
	int	pos;

	pos = 0;
	while (env_var[pos] != '$' && env_var[pos])
	{
		pos++;
	}
	printf("Im here!: %s, pos: %d\n", env_var, pos);
	printf("len: %d\n", len);
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
	printf("is_expand env_var: %s len: %d\n", env_var, len);
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
// char	*remove_quotes(char *str)
// {
// 	char	*ret;
// 	int		i[3];
// //	int		quotes;

// 	ft_bzero(i, 3 * sizeof(int));
// 	ret = NULL;
// //	quotes = str[0];
// //	printf("quotes in removing: %d\n", quotes);
// 	// if (quotes != '\"' && quotes != '\'')
// 	// 	return (str);
// 	while (str[i[0]])
// 	{
// 		if (/* str[i[0]] != quotes */str[i[0]] != '\'' && str[i[0]] != '\"')
// 			i[2]++;
// 		i[0]++;
// 	}
// 	ret = ft_calloc(i[2] + 1, sizeof(char));
// 	if (!ret)
// 		return (NULL);
// 	while (--i[0] > -1)
// 	{
// 		if (/* str[i[0]] != quotes */str[i[0]] != '\'' && str[i[0]] != '\"')
// 			ret[--i[2]] = str[i[0]];
// 	}
// 	free(str);
// 	return (ret);
// }

char	*remove_quotes(char *str)
{
	char	*ret;
	int		len;

	len = ft_strlen(str) - 2;
	ret = ft_substr(str, 1, len);
	free(str);
	return (ret);
}

int	compose_expanded(char *expanded, char **str, int dollar_pos, int end_pos)
{
	char	*preceding;
	char	*following;
	int		len;

	printf("str: %s\n", *str);
	preceding = ft_substr(*str, 0, dollar_pos);
	printf("preceding: %s\n", preceding);
	if (!preceding)
		return (0);
	// preceding = remove_quotes(preceding);
	// printf("preceding after remove quotes: %s\n", preceding);
	following = ft_substr(*str, end_pos, ft_strlen(*str) - end_pos);
	if (!following)
		return (free(preceding), -9);
	printf("following: %s\n", following);
//	if (ft_strlen(following) == 1 || *following == '\"')
	// if (!ft_strchr(following, '$'))
	// 	following = remove_quotes(following);
	// printf("following after remove quotes: %s\n", following);
	if (!expanded)
	{
		*str = ft_strjoin(preceding, following);
		printf("Line: %d:: str: %s\n", __LINE__, *str);
	}
	else
	{
		*str = ft_strjoin_many(3, preceding, expanded, following);
		printf("Line: %d:: str: %s\n", __LINE__, *str);
	}
	if (!(*str))
		return (free(preceding), free(following), -9);
	printf("str: %s, strlen: %ld\n", *str, ft_strlen(*str));
	if (expanded || (*preceding && !expanded))
	{
		printf("Line: %d make expanded...\n", __LINE__);
		if (*preceding && *following && expanded)
			len = ft_strlen(preceding) + ft_strlen(expanded) - 2;
		else if (*preceding && expanded)
			len = ft_strlen(preceding) + ft_strlen(expanded) - 1;
		else if (!expanded)
			len = ft_strlen(preceding) - 1;
		else
			len = ft_strlen(expanded) - 1;
		printf("expanded is: %s len: %d\n", expanded, len);
	}
	// else if (preceding && !*expanded)
	// {
	// 	len = ft_strlen(preceding) + ft_strlen(expanded) - 2;
	// }
	else if (!*preceding || (!*expanded && !*preceding))//230919nimai: added
	{
		len = -1;
	}
	else
	{
		printf("expanded is null\n");
		printf("preceding is: %s\n", preceding);
		len = ft_strlen(preceding) - 1;
	}
	free(preceding);
	free(following);
	free(expanded);
	printf("len is: %d\n", len);
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
	printf("quotes: %d\n", quotes);
	if (!ft_isdigit((*str)[*pos]))
	{
		// if ((*str)[i[0]] == '\'')
		// 	i[0]++;
		if ((*str)[i[0]] && !ft_isspace((*str)[i[0]]) && (*str)[i[0]] != quotes)
			i[0]++;
		while ((*str)[i[0]] && !ft_isspace((*str)[i[0]]) && (*str)[i[0]] != quotes && (*str)[i[0]] != '$' && (*str)[i[0]] != '\'' && (*str)[i[0]] != '\"')
			i[0]++;
		if (ft_strncmp(&(*str)[*pos], "$$", 2) == 0)
			i[0]++;
	}
	//expanded_var = is_expand(&(*str)[*pos], i[0] - *pos, env, pid);
	if (quotes != '\'')
		expanded_var = is_expand(&(*str)[*pos], i[0] - *pos, env, pid);
	else
	{
		while ((*str)[i[0]] && (*str)[i[0]] != '\'')
			i[0]++;
		printf("quotes: %d, str: %s pos: %d i[0]: %d\n", quotes, *str, *pos, i[0]);
		expanded_var = ft_substr(*str, *pos, i[0] - *pos);
		printf("%d: expanded_var: %s str: %s i[0]: %d\n", __LINE__, expanded_var, *str, i[0]);
		i[0]++;
		// expanded_var = remove_quotes(expanded_var);
	}
	printf("str: %s\n", *str);
	printf("expanded_var: %s\n", expanded_var);
	*pos = compose_expanded(expanded_var, str, *pos, i[0]);
	printf("pos: %d\n", *pos);
	if (*pos == -9)//230919nimai: changed error number to use -1 as length
		return (1);
//	is_quote(quotes);
	if (!(*str))
		return (1);
	return (0);
}

int amount_quotes(char *str)
{
	int		i;
	int		ret;
	int		quote;
	// char	*tmp;

	i = -1;
	ret = 0;
	quote = 0;
	if (str[0] != '\'' && str[0] != '\"')
		ret++;
	while (str[++i])
	{
		// tmp = &str[i];
		// printf("tmp: %s\n", tmp);
		if (quote && str[i] == quote)//end of quote
		{
			quote = 0;
			if (str[i + 1] && str[i + 1] != '\'' && str[i + 1] != '\"')
				ret++;
		}
		else if (!quote && (str[i] == '\'' || str[i] == '\"'))
		{
			ret++;
			quote = str[i];
		}
	}
	// printf("ret: %d\n", ret);
	return (ret);
}

/**
 * @param i[0]: position for str, start pos
 * @param i[1]: position for ret
 * @param i[2]: quotes type(0, 34, 39)
 * @param i[3]: position for str, end pos
 */
char	**split_quotes(char *str)
{
	char	**ret;
	int		len;
	int		i[4];

	len = amount_quotes(str);
	ret = (char **)ft_calloc(len + 1, sizeof(char *));
	if (!ret)
		return (NULL);
	ft_bzero(i, 4 * sizeof(int));
	while (i[3] < (int)ft_strlen(str))
	{
		i[0] = i[3];
		printf("Line: %d: str[%d]: %s\n", __LINE__, i[0], &str[i[0]]);
		i[2] = is_quote(str[i[0]]);
		printf("Line: %d: i[2]: %c\n", __LINE__, i[2]);
		if (i[2])
			i[3]++;
		while (str[i[3]] && ((i[2] && str[i[3]] != i[2]) || (!i[2] && str[i[3] + 1] && str[i[3] + 1] != '\'' && str[i[3] + 1] != '\"')))
			i[3]++;
		ret[i[1]] = ft_substr(str, i[0], i[3] - i[0] + 1);
		is_quote(str[i[3]]);
		i[3]++;
		i[1]++;
	}
	return (ret);
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

//str is not null
	tab = split_quotes(str);

//test printer
	c = 0;
	while (tab[c])
	{
		printf("tab[%d]: %s\n", c, tab[c]);
		c++;
	}
//test printer
	c = 0;
	while (tab[c])
	{
		i = -1;
		printf(COLOR_RED"tab[%d]: %s%s\n", c, tab[c], COLOR_RESET);
		while (tab[c][++i])
		{
			quotes = is_quote(tab[c][i]);
			if (tab[c][i] == '$' && quotes != '\'')
			{
				if (expand(&tab[c], &i, quotes, env, pid))
					return (NULL);
			}
		}
		printf("BEFORE REMOVING tab[%d]: %s%s\n", c, tab[c], COLOR_RESET);
		if (tab[c][0] == '\'' || tab[c][0] == '\"')
			tab[c] = remove_quotes(tab[c]);
		printf("AFTER REMOVING tab[%d]: %s%s\n\n", c, tab[c], COLOR_RESET);
		if (c == 0)
			ret = ft_strdup(tab[c]);
		else
			ret = ft_strjoin(ret, tab[c]);
		c++;
	}
	return (ret);
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
