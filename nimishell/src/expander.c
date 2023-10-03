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

char	*tilde_expantion(char *tilde, char **env)
{
	char	*ret;

	ret = get_env(env, "HOME");
	if (!ret)
		ret = obtain_pwd_home(env, 2);
	my_free(tilde);
	return (ret);
}

/**
 * @note pieces[0] before $
 * @note pieces[1] expanded var
 * @note pieces[2] after var 
 */
/* int	expand(char **str, int *pos, int quotes, char **env, pid_t pid)
{
	int		i[2];
	char	*expanded_var;

	expanded_var = NULL;
	ft_bzero(i, 2 * sizeof(int));
	i[0] = *pos;
	i[0] = check_valiable_len(&(*str)[*pos], i[0], quotes);
	expanded_var = is_expand(&(*str)[*pos], i[0] - *pos, env, pid);
	*pos = compose_expanded(expanded_var, str, *pos, i[0]);
	if (*str[0] == '\"' && (ft_strncmp(*str, "$\"", 2) || ft_strncmp(*str, "$ ", 2)))
		*pos += 1;
	if (*pos == -9)//230919nimai: changed error number to use -1 as length
		return (1);
	if (!(*str))
		return (1);
	return (0);
} */

int	expand(char **str, int *pos, int quotes, t_data *data)
{
	int		i[2];
	char	*expanded_var;

	expanded_var = NULL;
	ft_bzero(i, 2 * sizeof(int));
	i[0] = *pos;
	i[0] = check_valiable_len(&(*str)[*pos], i[0], quotes);
	expanded_var = is_expand(&(*str)[*pos], i[0] - *pos, data->env, data->pid);
	*pos = compose_expanded(expanded_var, str, *pos, i[0]);
	if (*str[0] == '\"' && (ft_strncmp(*str, "$\"", 2) || ft_strncmp(*str, "$ ", 2)))
		*pos += 1;
	if (*pos == -9)//230919nimai: changed error number to use -1 as length
		return (1);
	if (!(*str))
		return (1);
	return (0);
}

/* int	obtain_expantion(char **str, char *env[], pid_t pid)
{
	int	i;
	int	quotes;

	i = -1;
	while ((*str)[++i])
	{
		quotes = is_quote((*str)[i]);
		if ((*str)[i] == '$' && quotes != '\'')
		{
			if (expand(str, &i, quotes, env, pid))
				return (0);
		}
	}
	return (1);
} */

int	obtain_expantion(char **str, t_data *data)
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
				return (0);
		}
	}
	return (1);
}

/* char	*expander(char *str, char *env[], pid_t pid)
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
			if (!obtain_expantion(&tab[c], env, pid))
			{
				free_list(tab);
				return (free (ret), NULL);
			}
		}
		else
			tab[c] = tilde_expantion(tab[c], env);
		ret = arrange_str(tab, ret, c);
	}
	return (free_list(tab), ret);
} */

char	*expander(char *str, t_data *data)
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
			if (!obtain_expantion(&tab[c], data))
			{
				free_list(tab);
				return (free (ret), NULL);
			}
		}
		else
			tab[c] = tilde_expantion(tab[c], data->env);
		ret = arrange_str(tab, ret, c);
	}
	return (free_list(tab), ret);
}

// char	*expander(char *str, char *env[], pid_t pid)
// {
// 	int		i;
// 	int		c;
// 	int		quotes;
// 	char	**tab;
// 	char	*ret;

// 	ret = NULL;
// 	tab = split_quotes(str);
// 	c = -1;
// 	while (tab[++c])
// 	{
// 		if (!ft_strcmp(tab[c], "~"))
// 			tab[c] = tilde_expantion(tab[c], env);
// 		else
// 		{
// 			i = -1;
// 			while (tab[c][++i])
// 			{
// 				quotes = is_quote(tab[c][i]);
// 				if (tab[c][i] == '$' && quotes != '\'')
// 				{
// 					if (expand(&tab[c], &i, quotes, env, pid))
// 						return (NULL);
// 				}
// 			}
// 		}
// 		ret = arrange_str(tab, ret, c);
// 	}
// 	return (free_list(tab), ret);
// }
