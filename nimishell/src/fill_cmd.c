/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-mada <bde-mada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:08:15 by bde-mada          #+#    #+#             */
/*   Updated: 2023/12/06 16:08:32 by bde-mada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_command(t_list *lst, int pos)
{
	int	ret;

	ret = 0;
	while (lst && lst->cmd_pos == pos)
	{
		if (lst->type == WORD || lst->type == PIPE || lst->type == QUOTE)
			ret++;
		lst = lst->next;
	}
	return (ret);
}

void	init_cmd(char ***cmd, char *str, int *i)
{
	if (i[1] == 5)
		*cmd = ft_split(str, ' ');
	else
	{
		*cmd = (char **)ft_calloc(2, sizeof(char *));
		(*cmd)[0] = ft_strdup(str);
		(*cmd)[1] = NULL;
	}
	i[0] = av_amount(*cmd);
}

/**
 * @param i[1]: flag
 * @param i[2]: type_flag
 * @param i[3]: old type_flag
  */
void	obtain_cmd(char ***cmd, char *str, int *i)
{
	char	**new;
	int		j;

	if (!str || !*str)
		return ;
	new = NULL;
	j = -1;
	if (!*cmd)
		init_cmd(cmd, str, i);
	else if (*cmd && **cmd)
	{
		new = (char **)ft_calloc(i[0] + 2, sizeof(char *));
		if (!new)
			return ;
		new[i[0] + 1] = NULL;
		new[i[0]] = ft_strdup(str);
		while (++j < i[0])
			new[j] = ft_strdup((*cmd)[j]);
		free_list(*cmd);
		*cmd = new;
	}
	i[0] = av_amount(*cmd);
}

/**
 * i[0]: i
 * i[1]: flag
 * i[2]: type_flag//not use
 * i[3]: old type_flag//not use
 * i[2]: variable count
  */
char	**fill_current_cmd(t_list *lst, int pos, t_data *data)
{
	char		**cmd;
	char		*expanded;
	int			i[3];

	ft_bzero(i, 3 * sizeof(int));
	i[0] = count_command(lst, pos);
	if (!i[0])
		return (NULL);
	cmd = NULL;
	i[0] = 0;
	while (lst && lst->cmd_pos == pos)
	{
		if (lst->type == WORD || lst->type == PIPE || lst->type == QUOTE)
			expanded = expander(lst->content, data, i);
		else
		{
			lst = lst->next;
			continue ;
		}
		obtain_cmd(&cmd, expanded, i);
		free (expanded);
		lst = lst->next;
	}
	return (cmd);
}
/* 	//DELETE
	if (cmd)
	{
		ft_printf(COLOR_CYAN"Printing cmd"COLOR_RESET"\n");
		int j = -1;
		while (cmd[++j])
			ft_printf("cmd[%d] = %s\n", j, cmd[j]);
	} */
