/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:12:28 by nimai             #+#    #+#             */
/*   Updated: 2023/06/20 13:13:43 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_H
# define BUILT_H

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

typedef struct s_data
{
	char		**env;
	char		**path;
	int			return_val;
//	t_tokens	*head;
}				t_data;

typedef struct s_export_box
{
	int		id;
//	long	pos;
	char	*name;
	char	*val;
	int		equal;
}	t_export_box;

/**
 * @brief to order export list
 */
typedef struct s_export
{
	t_export_box	box[ARGLIMIT];
	int				plen;
}	t_export;

int			built_exit(char **input);
int			built_pwd(t_data *data);
int			built_echo(char **input);
int			built_cd(char **input, t_data *data);
int			built_export(char **input, t_data *data);
int			built_env(char **input, t_data *data);
int			built_unset(char **input, t_data *data);

/**
 * functions from export
 */
int			av_amount(char **strs);
char		**fake_env(void);
t_export	*fill_list(char **strs, t_export *ret);
void		output_env(t_export *data, int len, int flag);
int			check_valid(char *str, char *cmd);
int			output_export(t_data *data);
char		**envp_strs_join(char *input, t_data *data);
void		envp_strs_mod(char *input, t_data *data);
int			check_input(char *input, t_data *data);
/**
 * functions from export
 */

/**
 * functions from cd
  */

t_data		*envp_cd_mod(t_data *data, char *dest, int path);
char		*ft_strlower(char *str);
char		*str_mod(char *cur, char *str, int i);
char		*path_modify(char *cur, char *str);
int			get_pos_above_path(char *str);
char		*get_above_path(char *cur, t_data *data);
void		error_cd(char *cmd, t_data *data);
char		*get_dest_path_wl_sign(t_data *data, char *cur);
char		*get_dest_path_env(t_data *data, char *envtype);
/**
 * functions from cd
  */

/**
 * functions from utils
 */

int			check_valid(char *str, char *cmd);
char		*get_env(char **env, char *type);
/**
 * functions from utils
 */

void		error_av_built(char *cmd, char *av, char *comment);
void		error_id_built(char *cmd, char *av, char *comment);
void		error_built(char *cmd, char *comment);
int			error_notset(char *cmd, char *input);
void		heap_error(int flag);
void		quick_sort(t_export_box box[], int left, int right);



void		**ptr_free(void **ptr);
void		*arr_free(t_export *list);
/* void		*all_tmp_free(t_temp *temp); */
char		**strs_free(char **strs);

#endif
