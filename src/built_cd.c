/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 18:40:39 by nimai             #+#    #+#             */
/*   Updated: 2023/05/24 12:45:43 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_cd()
{
	
}

/**
 * @brief get path length.
 * @author nimai
 * @note maybe already exist.
 */
int	get_path_length(char *str, int i)
{
	int	ret;

	ret = 0;
	while (str[i] && str[i] != 32)
	{
		ret++;
		i++;
	}
	return (ret);
}

/**
 * @brief get absolute path to move
 * @author nimai
 * @return destination path as string
 */
char	*get_dest_path(char *str)
{
	char	*ret;
	int		i;
	int		len;

	i = 0;
	ret = NULL;
	len = get_path_length(str, i);
	ret = (char *)ft_calloc(sizeof(char), (len + 1));
	ft_strlcpy(ret, str, len + 1);
	if (!check_path(ret))
		return (error_cd(), NULL);
	printf("ret: %s\n", ret);
	return (ret);
}

/**
 * @brief manage "builtin" cd cmd.
 * @author nimai
 * @param **av "cd", "path".
 * @return 
 */
int	built_cd(char **av)
{
	char	*dest;
	
	dest = get_dest_path(av[2]);
	if (!dest)
		return (0);//230524nimai: if it's null, don't have to move, so return (0)?

	ft_printf("minishell: cd: %s: No such file or directory\n", av[2]);
	return (0);
}

/**
 * if there are more than 1 path, it will ignore after the first.
 * 
 * /Users/nimai/42/42cursus/minishell/inc
 * bash-3.2$ cd ..
 * bash-3.2$ ls
 * Makefile	README.md	inc		lib		minishell	questions.txt	src		test.dat
 * bash-3.2$ cd /users/nimai/42/42cursus/minishell/inc
 * bash-3.2$ pwd
 * /users/nimai/42/42cursus/minishell/inc    <= ?????
 * 
 * printf("line: %d\n", __LINE__);
 * error message: ft_printf("No such file or directory\n");
 * how to treat "../" or "./", give message like above? Or put other message?
 */

