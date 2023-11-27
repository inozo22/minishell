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

int	obtain_expansion(char **str, t_data *data, int *flag)
{
	int	i;
	int	quotes;

	i = -1;
	while ((*str)[++i])
	{
		quotes = is_quote((*str)[i]);
		if ((*str)[i] == '$' && quotes != '\'')
		{
			if (expand(str, &i, quotes, data))
			{
				*flag = 2;
				ft_printf("NULL! expand. flag: %d\n", *flag);
				return (0);
			}
			*flag = 1;
			ft_printf("success! expand. flag: %d\n", *flag);
		}
		else
		{
			*flag = 0;
			ft_printf("success! expand. flag: %d\n", *flag);
		}
	}
	return (1);
}

char	*expander(char *str, t_data *data, int *flag)
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
			if (!obtain_expansion(&tab[c], data, flag))
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
