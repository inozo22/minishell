/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 10:18:56 by nimai             #+#    #+#             */
/*   Updated: 2023/10/02 14:30:20 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	envp_strs_mod(char *input, t_data *data)
{
	int		i[3];

	ft_bzero(i, 3 * sizeof(int));
	i[2] = check_input(input, data);
	if (input[i[2]] == '=')
	{
		while (data->env[i[0]])
		{
			i[1] = 0;
			if (ft_strncmp(data->env[i[0]], input, i[2] + 1) == 0)
				data->env[i[0]] = envp_str_mod(data->env[i[0]], input, i[2], 0);
			else if (ft_strncmp(data->env[i[0]], input, i[2]) == 0)
			{
				while (data->env[i[0]][i[1]] == input[i[1]])
					++i[1];
				if (data->env[i[0]][i[1]] == '\0' && input[i[1]] == '=')
				{
					data->env[i[0]] = envp_str_mod(data->env[i[0]], \
					input, i[2], 1);
					break ;
				}
			}
			i[0]++;
		}
	}
}

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
	return (ret);
}

/**
 * @brief add environment according to av in **
 * @author nimai
 * @return ** pointer, then free 
 */
char	**envp_strs_join(char *input, t_data *data)
{
	char	**ret;
	int		i;

	ret = ft_calloc(av_amount(data->env) + 2, sizeof(char *));
	if (!ret)
		return (heap_error(1), NULL);
	i = 0;
	while (data->env[i])
	{
		ret[i] = data->env[i];
		data->env[i] = NULL;
		i++;
	}
	free (data->env);
	data->env = NULL;
	input = mod_path(input);
	if (check_valid(input, "export"))
		ret[i] = input;
	ret[++i] = NULL;
	return (ret);
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
	while (++i < av_amount(input))
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
	return (g_return_val);
}

/**
 * BEHAVIOUR ON BASH
 * when execute export, the list should be ascending order, 
 * separated by capital letter and small letter-> done
 * If there is more than one argument after command, add as a variable,
 * except if there is no space
 * 
 * 230601nimai: I have doubt with $<variable name> ->treate as I have received
 * a path
 * 
 * ??? Is it OK if we control in the minishell?	-> OK!
 * For example, it's ok if do sth in bash, but doesn't affect to the
 * minishell? ->OK!
 * 
 * ******************************************************************
 * 230613nimai:
 * export OLDPWD: do nothing
 * export OLDPWD=aaa: overwrite
 * export OLDPWD="aaa": doesn't work (ask how will I receive)
 * <- 230614nimai: I think will receive as a string
 * export OLDPWA: add in export, but doesn't print with env command
 * export OLDPWA=aaa: add new variable
 * export OLDPWA="aaa": doesn't work (ask how will I receive)
 * 
 * 
 * ******************************************************************
 * Command to check
 * export a b c=aaa
 */
