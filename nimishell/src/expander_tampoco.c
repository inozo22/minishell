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

int	obtan_expanded_len(char *preceding, char *following, char *expanded)
{
	int	ret;

	if (expanded || (*preceding && !expanded))
	{
		if (*preceding && *following && expanded)
			ret = ft_strlen(preceding) + ft_strlen(expanded) - 2;
		else if (*preceding && expanded)
			ret = ft_strlen(preceding) + ft_strlen(expanded) - 1;
		else if (!expanded && *following == '\"')
			ret = ft_strlen(preceding);
		else if (!expanded)
			ret = ft_strlen(preceding) - 1;
		else
			ret = ft_strlen(expanded) - 1;
	}
	else if (!expanded && !*preceding && *following == '\"')
		ret = 0;
	else if (!*preceding || (!*expanded && !*preceding))
		ret = -1;
	else
		ret = ft_strlen(preceding) - 1;
	return (ret);
}

/**
 * @param i[0]: end position
 * @param i[1]: start position
 */
int	compose_expanded(char *expanded, char **str, int quotes, int i[2])
{
	char	*preceding;
	char	*following;
	int		len;

	printf("quotes in compose expanded: %d\n", quotes);
	printf("expanded: %s\n", expanded);
	preceding = ft_substr(*str, 0, i[1]);
	if (!preceding)
		return (0);
	printf("preceding: %s\n", preceding);
	preceding = remove_quotes(preceding, quotes);
	printf("preceding after remove quotes: %s\n", preceding);
	following = ft_substr(*str, i[0], ft_strlen(*str) - i[0]);
	if (!following)
		return (free(preceding), -9);
	printf("following: %s\n", following);
//	if (ft_strlen(following) == 1 || (expanded && *following == '\"'))
	following = remove_quotes(following, quotes);
	printf("following after remove quotes: %s\n", following);
	if (!expanded)
		*str = ft_strjoin(preceding, following);
	else
		*str = ft_strjoin_many(3, preceding, expanded, following);
	if (!(*str))
		return (free(preceding), free(following), -9);
	printf("str after compose: %s\n", *str);
	len = obtan_expanded_len(preceding, following, expanded);
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

	ft_bzero(i, 2 * sizeof(int));
	i[0] = *pos;
	i[1] = *pos;
	if (quotes/* (*str)[i[0]] == '\'' ||(*str)[i[0]] == '\"' */)
	 	i[0]++;
	printf("%dquotes: %d\n", __LINE__, quotes);
	if ((*str)[i[0]] && !ft_isspace((*str)[i[0]]) && (*str)[i[0]] != quotes && (quotes && (*str)[i[0]] == '$'))
		i[0]++;
	while ((*str)[i[0]] && !ft_isspace((*str)[i[0]]) && (*str)[i[0]] != '$' && ((quotes == 0 && ((*str)[i[0]] != '\'' && (*str)[i[0]] != '\"')) || (quotes != 0 && (*str)[i[0]] != quotes))/*  && (quotes == 0 && ((*str)[i[0]] != '\'' && (*str)[i[0]] != '\"')) && (*str)[i[0]] != quotes && (*str)[i[0]] != '$' */)
		i[0]++;
	if (ft_strncmp(&(*str)[*pos], "$$", 2) == 0)
		i[0]++;
	printf("hole str: %s\n", &(*str)[*pos]);
	printf("string!: %s\n", ft_substr(*str, *pos + 1, i[0] - *pos - 1));
	if (quotes)
		i[1] += 1;
	printf("string!: %s\n", ft_substr(*str, i[1], i[0] - i[1]));
	if (quotes != '\'')
		expanded_var = is_expand(&(*str)[i[1]], i[0] - i[1], env, pid);
	else
	{
		while ((*str)[i[0]] && (*str)[i[0]] != '\'')
			i[0]++;
		expanded_var = ft_substr(*str, i[1], i[0] - i[1]);
		i[0]++;
	//	printf("expanded_var with '': %s\n", expanded_var);
		expanded_var = remove_quotes(expanded_var, quotes);
	}
	*pos = compose_expanded(expanded_var, str, quotes, i);
	if (*pos == -9)
		return (1);
	is_quote(quotes);
	// if (!is_quote(quotes))
	// 	i[0]++;
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
		printf("%sstr in expander: %s%s\n", COLOR_YELLOW, &str[i], COLOR_RESET);
		quotes = is_quote(str[i]);
		printf("%dquotes: %d\n", __LINE__, quotes);
		while (str[i] && ft_isspace(str[i]))
			i++;
		if (str[i] == '$' || (quotes && str[i + 1] == '$'))
		{
			if (expand(&str, &i, quotes, env, pid))
				return (NULL);
		}
		else
		{
			if (quotes)
			{ 
				while (str[++i] != quotes)
					;
			}
			printf("str without expand: %s\n", &str[i]);
			printf("str without expand: %s\n", str);
		}
		if (i >= 0 && !str[i])
			break ;
	}
	return (str);
}
