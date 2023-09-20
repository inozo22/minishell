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
		return (free(preceding), -9);
	if (ft_strlen(following) == 1 || *following == '\"')
		following = remove_quotes(following);
	if (!expanded)
		*str = ft_strjoin(preceding, following);
	else
		*str = ft_strjoin_many(3, preceding, expanded, following);
	if (!(*str))
		return (free(preceding), free(following), -9);
	if (expanded || (*preceding && !expanded))
	{
		if (*preceding && *following && expanded)
			len = ft_strlen(preceding) + ft_strlen(expanded) - 2;
		else if (*preceding && expanded)
			len = ft_strlen(preceding) + ft_strlen(expanded) - 1;
		else if (!expanded)
			len = ft_strlen(preceding) - 1;
		else
			len = ft_strlen(expanded) - 1;
	}
	else if (!*preceding || (!*expanded && !*preceding))
		len = -1;
	else
		len = ft_strlen(preceding) - 1;
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
	if ((*str)[*pos]/* !ft_isdigit((*str)[*pos]) */)
	{
		if ((*str)[i[0]] == '\'')
			i[0]++;
		if ((*str)[i[0]] && !ft_isspace((*str)[i[0]]) && (*str)[i[0]] != quotes)
			i[0]++;
		while ((*str)[i[0]] && !ft_isspace((*str)[i[0]]) && (*str)[i[0]] != quotes && (*str)[i[0]] != '$' && (*str)[i[0]] != '\'' && (*str)[i[0]] != '\"')
			i[0]++;
		if (ft_strncmp(&(*str)[*pos], "$$", 2) == 0)
			i[0]++;
	}
	if (quotes != '\'')
		expanded_var = is_expand(&(*str)[*pos], i[0] - *pos, env, pid);
	else
	{
		while ((*str)[i[0]] && (*str)[i[0]] != '\'')
			i[0]++;
		expanded_var = ft_substr(*str, *pos, i[0] - *pos);
		i[0]++;
		expanded_var = remove_quotes(expanded_var);
	}
	*pos = compose_expanded(expanded_var, str, *pos, i[0]);
	if (*pos == -9)
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
		while (str[i] && ft_isspace(str[i]))
			i++;
		if (str[i] == '$' || (quotes && str[i + 1] == '$'))
		{
			if (expand(&str, &i, quotes, env, pid))
				return (NULL);
		}
		if (i >= 0 && !str[i])
			break ;
	}
	return (str);
}
