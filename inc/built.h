/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:12:28 by nimai             #+#    #+#             */
/*   Updated: 2023/05/25 11:29:54 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_H
# define BUILT_H

# include "minishell.h"

# define ARGLIMIT 501

/**
 * @brief to order export list
 * @author nimai
 * @param index the final position number.
 * @param pos the amount of the name, do letter to long.
 * @param name keep until "="
 * @param val valor of variable, I have to put " " when I output
 */
typedef struct s_export
{
	int		index;
	long	pos;
	char	*name;
	char	*val;
}	t_export;

int		built_exit(char **av);
int		built_pwd(char **av);
int		built_echo(char **av);
int		built_cd(char **av);
int		built_export(char **av);
int		av_amount(char **strs);
void	heap_error(int flag);



#endif