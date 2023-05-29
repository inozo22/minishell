/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:12:14 by nimai             #+#    #+#             */
/*   Updated: 2023/05/29 14:16:08 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "minishell.h"
# include <signal.h>

/**
 * @brief smalll boxes
 * @author nimai
 * @param index the final position number.
 * @param pos the amount of the name, do letter to long.
 * @param name keep until "="
 * @param val valor of variable, I have to put " " when I output
 */
typedef struct s_export_box
{
	int		id;
	long	pos;
	char	*name;
	char	*val;
}	t_export_box;

/**
 * @brief to order export list
 */
typedef struct s_export
{
	t_export_box	box[ARGLIMIT];
	int				plen;
}	t_export;

/**
 * functions from export
 */

/**
 * functions from export
 */





#endif