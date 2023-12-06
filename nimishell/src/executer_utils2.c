/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-mada <bde-mada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:03:23 by bde-mada          #+#    #+#             */
/*   Updated: 2023/12/06 16:12:15 by bde-mada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

int	check_is_directory(char *cmd)
{
	struct stat	t_stat;

	if (!stat(cmd, &t_stat) && S_ISDIR(t_stat.st_mode))
	{
		if (cmd[0] == '/' || cmd[ft_strlen(cmd) - 1] == '/')
			return (3);
		else
			return (1);
	}
	return (0);
}

/**
 * @author bde-mada
 * @param path[0] = tmp_path
 * @param path[1] = cmd_path
*/
char	*get_cmd_path(char *cmd, char **path, int *return_val)
{
	int			i;
	char		*cmd_path[2];

	i = -1;
	ft_bzero(cmd_path, 2 * sizeof(char *));
	*return_val = check_is_directory(cmd);
	if (*return_val)
		return (NULL);
	if (!access(cmd, F_OK))
		return (cmd);
	while (path && path[++i])
	{
		cmd_path[0] = ft_strjoin(path[i], "/");
		if (cmd_path[0] && cmd)
			cmd_path[1] = ft_strjoin(cmd_path[0], cmd);
		free(cmd_path[0]);
		if (!access(cmd_path[1], F_OK))
			break ;
		free(cmd_path[1]);
		cmd_path[1] = NULL;
	}
	if (!cmd_path[1])
		*return_val = 1;
	return (cmd_path[1]);
}
//	ft_printf("cmd_path: %s\n\n", cmd_path[1]);
