/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 15:48:45 by nimai             #+#    #+#             */
/*   Updated: 2023/09/26 15:50:19 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @note call in function expander
 */
char	*arrange_str(char **tab, char *str, int c)
{
	char	*ret;

	if (tab[c][0] == '\'' || tab[c][0] == '\"')
		tab[c] = remove_quotes(tab[c]);
	ret = ft_strjoin(str, tab[c]);
	free (str);
	str = NULL;
	return (ret);
}

char	*remove_quotes(char *str)
{
	char	*ret;
	int		len;

	len = ft_strlen(str) - 2;
	ret = ft_substr(str, 1, len);
	free(str);
	return (ret);
}

int	expanded_len(char *expanded, char *preceding, char *following)
{
	int	ret;

	if (expanded || (*preceding && !expanded))
	{
		if (*preceding && *following && expanded)
			ret = ft_strlen(preceding) + ft_strlen(expanded) - 2;
		else if (*preceding && expanded)
			ret = ft_strlen(preceding) + ft_strlen(expanded) - 1;
		else if (!expanded)
			ret = ft_strlen(preceding) - 1;
		else
			ret = ft_strlen(expanded) - 1;
	}
	else
		ret = ft_strlen(preceding) - 1;
	return (ret);
}

int	amount_quotes(char *str)
{
	int		i;
	int		ret;
	int		quote;

	ret = 0;
	quote = 0;
	if (str[0] != '\'' && str[0] != '\"')
		ret++;
	i = -1;
	while (str[++i])
	{
		if (quote && str[i] == quote)
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
		return (NULL);//
	ft_bzero(i, 4 * sizeof(int));
	while (i[3] < (int)ft_strlen(str))
	{
		i[0] = i[3];
		i[2] = is_quote(str[i[0]]);
		if (i[2])
			i[3]++;
		while (str[i[3]] && ((i[2] && str[i[3]] != i[2]) || \
		(!i[2] && str[i[3] + 1] && str[i[3] + 1] != '\'' && \
		str[i[3] + 1] != '\"')))
			i[3]++;
		ret[i[1]] = ft_substr(str, i[0], i[3] - i[0] + 1);
		is_quote(str[i[3]]);
		i[3]++;
		i[1]++;
	}
	return (ret);
}
