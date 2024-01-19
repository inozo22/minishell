/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:29:23 by nimai             #+#    #+#             */
/*   Updated: 2023/12/07 13:29:23 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*tilde_expansion(char *tilde, t_data *data)
{
	char	*ret;

	ret = get_env(data->env, "HOME");
	if (!ret)
		ret = obtain_pwd_home(data, 2);
	my_free(tilde);
	return (ret);
}

int	expand(char **str, int *pos, int quotes, t_data *data)
{
	int		i[2];
	char	*expanded_var;

	expanded_var = NULL;
	ft_bzero(i, 2 * sizeof(int));
	i[0] = *pos;
	i[0] = check_variable_len(&(*str)[*pos], i[0], quotes);
	expanded_var = is_expand(&(*str)[*pos], i[0] - *pos, data);
	if (quotes && !expanded_var)
	{
		*pos = -1;
		return (1);
	}
	*pos = compose_expanded(expanded_var, str, *pos, i[0]);
	if (*str[0] == '\"' && (ft_strncmp(*str, "$\"", 2) || \
	ft_strncmp(*str, "$ ", 2)))
		*pos += 1;
	if (*pos == -9)
		return (1);
	if (!(*str))
		return (1);
	return (0);
}

/**
 * @param i[0] pos index
 * @param i[1] flag
 * @param i[2] variable count
 */
int	obtain_expansion(char **str, t_data *data, int *i)
{
	int	n;
	int	quotes;

	n = -1;
	while (*str && (*str)[++n])
	{
		quotes = is_quote((*str)[n]);
		if ((*str)[n] == '$' && quotes != '\'')
		{
			++i[2];
			if (expand(str, &n, quotes, data))
				return (i[1] = 99, 0);
			if (i[2] == 1)
				i[1] = 5;
			if (i[2] == 2 && quotes)
				i[1] = 1;
		}
		else
			if (!i[1])
				i[1] = 2;
	}
	if (quotes)
		is_quote((*str)[n - 1]);
	return (1);
}

char	*expander(char *str, t_data *data, int *i)
{
	int		c;
	char	**tab;
	char	*ret;

	ret = NULL;
	tab = split_quotes(str);
	c = -1;
	while (tab[++c])
	{
		if (ft_strcmp(tab[c], "~"))
		{
			if (!obtain_expansion(&tab[c], data, i))
			{
				free_list(tab);
				return (free (ret), NULL);
			}
		}
		else
			tab[c] = tilde_expansion(tab[c], data);
		ret = arrange_str(tab, ret, c);
	}
	return (free_list(tab), ret);
}

// int	obtain_expansion(char **str, t_data *data, int *i)
// {
// 	int	n;
// 	int	quotes;

// 	n = 0;
// 	while (n >= 0 && *str && (*str)[n])
// 	{
// 		quotes = is_quote((*str)[n]);
// 		ft_printf("(*str)[%d]: %s\n", n, &(*str)[n]);
// 		if ((*str)[n] == '$' && quotes != '\'')
// 		{
// 			++i[2];
// 			if (expand(str, &n, quotes, data))
// 				return (i[1] = 99, 0);
// 			if (i[2] == 1)
// 				i[1] = 5;
// 			if (i[2] == 2 && quotes)
// 				i[1] = 1;
// 			ft_printf("(*str)[%d]: %s\n", n, &(*str)[n]);
// 			// n -= 1;
// 		}
// 		else
// 			if (n++ && !i[1])
// 				i[1] = 2;
// 		ft_printf("n: %d\n", n);
// 	}
// 	if (quotes)
// 		is_quote((*str)[n - 1]);
// 	return (1);
// }
