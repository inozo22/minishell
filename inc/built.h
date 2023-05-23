/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:12:28 by nimai             #+#    #+#             */
/*   Updated: 2023/05/23 18:42:58 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_H
# define BUILT_H

# include "minishell.h"

int	built_exit(char **av);
int	built_pwd(char **av);
int	built_echo(char **av);
int	built_cd(char **av);
int	av_amount(char **strs);



#endif