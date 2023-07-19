/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 10:18:56 by nimai             #+#    #+#             */
/*   Updated: 2023/06/23 17:38:47 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	*envp_str_mod(char *str, char *input, int i, int flag)
{
	free (str);
	str = ft_calloc(ft_strlen(input) + 1 + flag, sizeof(char));
	if (!str)
	{
		return (NULL);
	}
	ft_strlcpy(str, input, i + 2);
	ft_strcat(str, (input + i + 1));
	return (str);
}

/**
 * 
 * @param i[0] : i
 * @param i[1] : j
 * @param i[2] : k
 * @param i[3] : c
 */
void	envp_strs_mod(char *input, t_data *data)
{
	int		i[3];

	ft_bzero(i, 3 * sizeof(int));
	i[2] = check_input(input, data);
	if (input[i[2]] == '=')
	{
		while (data->env[i[0]])
		{
			i[1] = -1;
			if (ft_strncmp(data->env[i[0]], input, i[2] + 1) == 0)//with '='
			{
				data->env[i[0]] = envp_str_mod(data->env[i[0]], input, i[2], 0);
/* 				free (data->env[i[0]]);
				data->env[i[0]] = ft_calloc(ft_strlen(input) + 1, sizeof(char));
				ft_strlcpy(data->env[i[0]], input, i[2] + 2);
				ft_strcat(data->env[i[0]], (input + i[2] + 1)); */
				break ;
			}
			else if (ft_strncmp(data->env[i[0]], input, i[2]) == 0)
			{
				while (data->env[i[0]][++i[1]] == input[i[1]])
					;
				if (data->env[i[0]][i[1]] == '\0' && input[i[1]] == '=')
				{
					data->env[i[0]] = envp_str_mod(data->env[i[0]], input, i[2], 1);
/* 					data->env[i[0]] = ft_calloc(ft_strlen(input) + 2, 1);
					ft_strlcpy(data->env[i[0]], input, i[2] + 2);
					ft_strcat(data->env[i[0]], (input + i[2] + 1)); */
					break ;
				}
			}
			i[0]++;
		}
	}
}

/**
 * @brief modify environment according to av in **
 * @author nimai
 * @return nothing, it's a void function
 * @note 230613nimai: if change the input style, modify here
 * @note 230620nimai: it's required to control here
 */
/* void	envp_strs_mod(char *input, t_data *data)
{
	char	*tmp;
	int		i;
	int		j;
	int		k;
	int		c;

	i = 0;

	c = check_input(input, data);
	if (input[c] == '=')
	{
		while (data->env[i])
		{
			j = -1;
			k = -1;
			if (ft_strncmp(data->env[i], input, c + 1) == 0)//with '='
			{
				free (data->env[i]);
				tmp = ft_calloc(ft_strlen(input) + 1, sizeof(char));
				ft_strlcpy(tmp, input, c + 2);
				ft_strcat(tmp, (input + c + 1));
				data->env[i] = tmp;
				break ;
			}
			else if (ft_strncmp(data->env[i], input, c) == 0)
			{
				while (data->env[i][++j] == input[++k])
					;
				if (data->env[i][j] == '\0' && input[k] == '=')
				{
					tmp = ft_calloc(ft_strlen(input) + 2, sizeof(char));
					ft_strlcpy(tmp, input, c + 2);
					ft_strcat(tmp, (input + c + 1));
					data->env[i] = tmp;
					break ;
				}
			}
			i++;
		}
	}
} */

/**
 * @return 1, when it's quotes 
 */
int	check_quotes(char *input, int i, int flag)
{
	if (flag)
	{
		if ((i > 2 && input[i - 1] == '=' && input[i] == '\"') || \
		(input[i] == '\"' && input[i + 1] == '\0'))
			return (1);
		else if ((i > 2 && input[i - 1] == '=' && input[i] == '\'') || \
		(input[i] == '\'' && input[i + 1] == '\0'))
			return (1);
	}
	return (0);
}

/**
 * @param i[0] counter for input
 * @param i[1] counter for ret
 * @param i[2] flag if there is quotes
 */
char	*mod_path(char *input)
{
	int		i[3];
	char	*ret;

	ft_bzero(i, 3 * sizeof(int));
	while (input[i[0]])
	{
		if (input[i[0]] == '=' && input[i[0] + 1] == '\"')
			i[2] = 2;
		else if (input[i[0]] == '=' && input[i[0] + 1] == '\'')
			i[2] = 2;
		i[0]++;
	}
	ret = ft_calloc(ft_strlen(input) + 1 - i[2], sizeof(char *));
	if (!ret)
		return (NULL);
	i[0] = 0;
	while (input[i[0]])
	{
		if (!check_quotes(input, i[0], i[2]))
			ret[i[1]++] = input[i[0]];
		i[0]++;
	}
	ret[i[1]] = '\0';
	free (input);
	return (ret);
}

/**
 * @brief add environment according to av in **
 * @author nimai
 * @return ** pointer, then free 
 * @note 230530nimai: I will throw it away
 */
char	**envp_strs_join(char *input, t_data *data)
{
	char	**ret;
	int		i;
	int		j;

	ret = ft_calloc(av_amount(data->env) + 2, sizeof(char *));
	if (!ret)
		return (heap_error(1), NULL);
	i = 0;
	j = 0;
	while (data->env[i])
	{
		ret[i] = data->env[i];
		data->env[i] = NULL;
		i++;
	}
	free (data->env);
	data->env = NULL;
	input = mod_path(input);
	if (check_valid(input, "export", data))
		ret[i] = input;
	ret[++i] = NULL;
	return (ret);
}

int	check_input(char *input, t_data *data)
{
	int	c;
	int	i;
	int	j;


	i = 0;
	while (data->env[i])
	{
		c = 0;
		j = -1;
		while (data->env[i][++j] == input[c] && input[c] != '=' \
		&& input[c] != '\0' && data->env[i][j])
			c++;
		if ((input[c] == '=' && data->env[i][j] == '\0') || (data->env[i][j] \
		== '=' && input[c] == '\0') || (data->env[i][j] == input[c]))
			return (c);
		i++;
	}
	return (0);
}

/**
 * @brief manage "builtin" export cmd.
 * @author nimai
 * @param **input "export", "ABC=abc". *data
 * @return 
 */
int	built_export(char **input, t_data *data)
{
	char		**new_envp;
	int			i;

	new_envp = NULL;
	if (av_amount(input) == 1)
	{
		if (!output_export(data))
			return (printf("Error: output_export\n"), 1);
		return (0);
	}
	i = 0;
	while (input[++i])
	{
		if (!check_input(input[i], data))
		{
			new_envp = envp_strs_join(input[i], data);
			if (!new_envp)
				return (printf("ERROR: Line: %d\n", __LINE__), 1);
			data->env = new_envp;
		}
		else
			envp_strs_mod(input[i], data);
	}
	return (0);
}

/**
 * BEHAVIOUR ON BASH
 * when execute export, the list should be ascending order, 
 * separated by capital letter and small letter-> done
 * If there is more than one argument after command, add as a variable, 
 * except if there is no space
 * 
 * 230601nimai: I have doubt with $<variable name> ->treate as I have received a path
 * 
 * ??? Is it OK if we control in the minishell?	-> OK!
 * For example, it's ok if do sth in bash, but doesn't affect to the minishell? ->OK!
 * 
 * ******************************************************************
 * 230613nimai:
 * export OLDPWD: do nothing
 * export OLDPWD=aaa: overwrite
 * export OLDPWD="aaa": doesn't work (ask how will I receive) <- 230614nimai: I think will receive as a string
 * export OLDPWA: add in export, but doesn't print with env command
 * export OLDPWA=aaa: add new variable
 * export OLDPWA="aaa": doesn't work (ask how will I receive)
 */
