/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 09:50:16 by nimai             #+#    #+#             */
/*   Updated: 2023/10/02 13:59:59 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief temporary error management
 * @author nimai
 * @note in bash, treat another way, but as it doesn't ask to conrol neither
 * option nor flags, I have invented an error
 */
void	error_input(char *input, char *msg)
{
	ft_printf("minishell: %s: %s\n", input, msg);
}

/**
 * @brief manage "builtin" env cmd.
 * @author nimai
 * @param **av "env", no flags, no arguments
 * @return 
 * @note if there is no '=', understand that without value,
 * and not will print it
 */
int	built_env(char **input, t_data *data)
{
	char		**tmp_env;
	int			i;
	int			len;

	if (av_amount(input) > 1)
		return (error_input(input[0], \
				"with no options or arguments are required"), 1);
	tmp_env = (char **)data->env;
	if (!tmp_env)
		return (printf("ERROR: Line: %d\n", __LINE__), 0);
	i = 0;
	len = av_amount((char **)tmp_env);
	while (i < len)
	{
		if (ft_strrchr(tmp_env[i], '='))
			ft_printf("%s\n", tmp_env[i]);
		i++;
	}
	return (0);
}
