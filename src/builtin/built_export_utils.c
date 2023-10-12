/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 14:25:44 by nimai             #+#    #+#             */
/*   Updated: 2023/10/02 14:30:17 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * 
 * @param flag if there is no '=', you will put one more length to
 * allocate memory
 */
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
