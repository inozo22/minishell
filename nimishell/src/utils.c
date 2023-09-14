/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 12:49:14 by bde-mada          #+#    #+#             */
/*   Updated: 2023/09/14 14:46:14 by nimai            ###   ########.fr       */
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
	*ptr = NULL;
	return (ptr);
}

/*	int j = 0;
 	while (*ptr && *ptr[j])
	{
		ft_printf("lis: %d content: %s\n", j, *(ptr[j]));
		j++;
	} */
void	*del_array(void ***ptr)
{
	int	i;

	i = -1;
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

/**
 * @note in bash, not only print last command, but also last variable
 */
int	update_last_executed_cmd(t_data *data, char **input)
{
	char	**tmp_input;
	int		len;
	char	*cmd;

	if (ft_strchr(input[av_amount(input) - 1], '='))
	{
		len = ft_strlen(input[av_amount(input) - 1]) - \
		ft_strlen(ft_strchr(input[av_amount(input) - 1], '='));
		cmd = ft_calloc(len + 1, 1);
		if (!cmd)
			return (errors(ENOMEM, data));
		ft_strlcpy(cmd, input[av_amount(input) - 1], len + 1);
	}
	else
		cmd = ft_strdup(input[av_amount(input) - 1]);
	if (!ft_strcmp(cmd, "$_"))
		return (free (cmd), 0);
	tmp_input = (char **)ft_calloc(2 + 1, sizeof(char *));
	if (!tmp_input)
		return (free (cmd), errors(ENOMEM, data));
	tmp_input[0] = ft_strdup("export");
	tmp_input[1] = ft_strjoin("_=", cmd);
	ft_printf("tmp_input[0]: %s\n", tmp_input[0]);
	ft_printf("tmp_input[1]: %s\n", tmp_input[1]);
	built_export(tmp_input, data);
	return (free_list(tmp_input), free (cmd), 0);
}
// int	update_last_executed_cmd(t_data *data, char *cmd)
// {
// 	char	**tmp_input;

// 	tmp_input = (char **)ft_calloc(2 + 1, sizeof(char *));
// 	if (!tmp_input)
// 		return (errors(ENOMEM, data));
// 	tmp_input[0] = ft_strdup("export");
// 	tmp_input[1] = ft_strjoin("_=", cmd);
// 	ft_printf("tmp_input[0]: %s\n", tmp_input[0]);
// 	ft_printf("tmp_input[1]: %s\n", tmp_input[1]);
// 	built_export(tmp_input, data);
// 	free_list(tmp_input);
// 	return (0);
// }
