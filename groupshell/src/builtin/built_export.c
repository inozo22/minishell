/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 10:18:56 by nimai             #+#    #+#             */
/*   Updated: 2023/06/16 11:56:13 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief add environment according to av in **
 * @author nimai
 * @return ** pointer, then free 
 * @note 230613nimai: if change the input style, modify here
 */
void	envp_strs_mod(char *input, t_data *data)
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
			//	free (data->env[i]);
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
/* 	else if (input[c] == '\0')//Do nothing
	{
		;
	} */
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

	ret = (char **)malloc(sizeof(char *) * (av_amount(data->env) + 2));
	if (!ret)
		return (heap_error(1), NULL);
	i = 0;
	j = 0;
	while (data->env[i])
	{
		ret[i] = data->env[i];
		i++;
	}
	if (check_valid(input, "export"))
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
		while (data->env[i][++j] == input[c] && input[c] != '=' && input[c] != '\0' && data->env[i][j])
			c++;
		if ((input[c] == '=' && data->env[i][j] == '\0') || (data->env[i][j] == '=' && input[c] == '\0') || (data->env[i][j] == input[c]))
			return (c);
		i++;
	}
	return (0);
}

/**
 * @brief manage "builtin" export cmd.
 * @author nimai
 * @param **av "export", "ABC=abc".
 * @return 
 */
int	built_export(char **input, t_data *data)
{
//	char		**tmp_env = NULL;
//	char		**av = NULL;
	char		**new_envp = NULL;
	int			i;
	int			j;

	if (av_amount(input) == 1)
	{
		if (!output_export(data))
			return (printf("Error: output_export\n"), 1);
		return (0);
	}
	i = -1;
	j = 0;
	while (input[++j])//input[1]start
	{
		if (!check_input(input[j], data))//add
		{
			new_envp = envp_strs_join(input[j], data);
			if (!new_envp)
				return (printf("ERROR: Line: %d\n", __LINE__), 1);
			data->env = new_envp;
		}
		else//mod
		{
			envp_strs_mod(input[j], data);
		}
	}
//If none of the above apply
/* 	if (!output_export(data))
		return (printf("Error: output_export\n"), 1); */
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
