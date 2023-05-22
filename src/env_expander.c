/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 12:29:54 by nimai             #+#    #+#             */
/*   Updated: 2023/05/22 18:29:58 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*exp_expand_env_and_join(char *ret, char *str, int len)
{
	char	*keyname;
	char	*env_val;
	char	*tmp;

	keyname = ft_substr(str, 0, len);
	if (!keyname)
		return (NULL);
	env_val = get_env_val(keyname);
	if (env_val)
	{
		if (ret)
		{
			tmp = ret;
			ret = ft_strjoin(ret, env_val);
			free(tmp);
		}
		else
			ret = ft_strdup(env_val);
		free (env_val);
	}
	free (keyname);
	return (ret);
}

char	*exp_ret_join_normal_str(char *ret, char *str, int *len)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_substr(str, 0, len);
	if (!tmp)
		return (NULL);
	if (!ret)
		ret = tmp;
	else
	{
		tmp2 = ret;
		ret = ft_strjoin(ret, tmp);
		free (tmp);
		free (tmp2);
	}
	return (ret);
}

bool	exp_will_toggle_env(bool is_env, bool is_unexpand, char *str, int len)
{
	bool	will_start;
	bool	will_end;

	will_start = !is_unexpand && str[len] == '$' && (len < (int)ft_strlen(str) && ft_isalnum(str[len + 1]) || str[len + 1] == '-' || str[len + 1] == '?');
	will_end = is_env && (!(ft_isalnum(str[len]) || str[len] == '_'	|| (len == 0 && str[len] == '?')) || (len == 1 && str[len - 1] == '?'));
	return (will_start || will_end || !str[len]);
}

bool	exp_join_str_or_env(char **ret, char **str, int *len, bool *is_env)
{
	if (*is_env)
		*ret = exp_expand_env_and_join(*ret, *str, *len);
	else
		*ret = exp_ret_join_normal_str(*ret, *str, *len);
	if (!(*str)[*len] || !ret)
		return (false);
	*str += *len + !*is_env;
	*len = 0;
	*is_env = !*is_env;
	return (true);
}

char	*expand_env_var(char *str)
{
	int		len;
	char	*ret;
	bool	is_env;
	bool	is_unexpand;
	bool	is_continued;

	len = 0;
	ret = NULL;
	is_env = false;
	is_unexpand = false;
	is_continued = true;
	while (is_continued)
	{
		if (str[len] == '\'' && !(len > 0 && str[len - 1] == '\\'))
			is_unexpand = !is_unexpand;
		if (exp_will_toggle_env(is_env, is_unexpand, str, len))
			is_continued = exp_join_str_or_env(&ret, &str, &len, &is_env);
		/* kokomade */
	}



}
