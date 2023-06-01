/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:12:28 by nimai             #+#    #+#             */
/*   Updated: 2023/06/01 09:53:15 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_H
# define BUILT_H

# include "minishell.h"

# define ARGLIMIT 501
# define PATHLIMIT 4096
# define SORT_VALUE 1
# define SORT_ID 0
# define FLAGEXPORT 1
# define FLAGENV 0

typedef struct s_temp	t_temp;

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

int			built_exit(t_temp *temp);
int			built_pwd(t_temp *temp);
int			built_echo(t_temp *temp);
int			built_cd(t_temp	*temp);
int			built_export(t_temp *temp);
int			built_env(t_temp *temp);
int			built_unset(t_temp *temp);

/**
 * functions from export
 */
int			av_amount(char **strs);
char		**fake_env(void);
t_export	*fill_list(char **strs, t_export *ret);
void		output_env(t_export *list, int len, int flag);
/**
 * functions from export
 */

void		heap_error(int flag);
void		quick_sort(t_export_box box[], int left, int right);

void		**ptr_free(void **ptr);
void		*arr_free(t_export *list);
/* void		*all_tmp_free(t_temp *temp); */
char		**strs_free(char **strs);



#endif