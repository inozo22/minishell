/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-mada <bde-mada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 12:49:14 by bde-mada          #+#    #+#             */
/*   Updated: 2023/09/05 16:09:55 by bde-mada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isquote(int c)
{
	if (c == '\'' || c == '\"')
		return (c);
	return (0);
}

void	*del(void **ptr)
{
	free(*ptr);
	ptr = NULL;
	return (ptr);
}

void	*del_array(void ***ptr)
{
	int	i;

	i = -1;
/*	int j = 0;
 	while (*ptr && *ptr[j])
	{
		ft_printf("lis: %d content: %s\n", j, *(ptr[j]));
		j++;
	} */
	while (*ptr && *ptr[++i] != NULL)
		del((void **)ptr[i]);
	free(*ptr);
	*ptr = NULL;
	return (ptr);
}

void	*del_err_array(char ***ptr, int i)
{
	while (i)
		del((void **)ptr[i--]);
	free(*ptr);
	*ptr = NULL;
	return (ptr);
}

int	update_last_executed_cmd(t_data *data, char *cmd)
{
	char	**tmp_input;

	tmp_input = (char **)ft_calloc(2 + 1, sizeof(char *));
	if (!tmp_input)
		return (errors(ENOMEM, data));
	tmp_input[0] = ft_strdup("export");
	tmp_input[1] = ft_strjoin("_=", cmd);
	built_export(tmp_input, data);
	free_list(tmp_input);
	return (0);
}
