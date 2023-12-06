/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-mada <bde-mada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:12:28 by nimai             #+#    #+#             */
/*   Updated: 2023/12/06 15:39:06 by bde-mada         ###   ########.fr       */
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
# define MSG_CD_CANT_ACCESS "cd: error retrieving current directory: \
getcwd: cannot access parent directories: No such file or directory"
# define MSG_CD_FAIL "failure to move to current directory\n"

//# include <termios.h>

typedef struct s_temp	t_temp;

typedef struct s_data
{
	char		**env;
	pid_t		pid;
	pid_t		max_pid;
	short int	exit_status;
	int			return_val;
	int			cmd_nb;
	int			tmp_stdio_fd[2];
	int			process_fd[2];
	int			pipe_fd[2];
}				t_data;

typedef struct s_export
{
	char			*content;
	char			*name;
	struct s_export	*next;
}				t_export;

/**
 * Main built-in functions
*/

// int			built_exit(char **input, t_data *data, int cmd_num);
// int			built_pwd(char **env);
// int			built_echo(char **input);
// int			built_cd(char **input, char ***env);
// int			built_export(char **input, char ***env);
// int			built_env(char **input, char **env);
// int			built_unset(char **input, char ***env);
int			built_exit(char **input, t_data *data, int cmd_num);
int			built_pwd(t_data *data);
// int			built_echo(char **input, t_data *data);
int			built_echo(char **input, t_data *data);
int			built_cd(char **input, t_data *data);
int			built_export(char **input, t_data *data);
// int			built_env(char **input, t_data *data);
int			built_env(char **input, t_data *data);
int			built_unset(char **input, t_data *data);

/**
 * functions from export
 */

char		**fake_env(void);
t_export	*fill_list(char **env, t_export *list);
// void		output_env(t_export *data, int len);
int			output_export(char **env);
// char		**envp_strs_join(char *input, char **env);
char		**envp_strs_join(char *input, t_data *data);
void		envp_strs_mod(char *input, char ***env);
int			check_input(char *input, char **env);
char		*envp_str_mod(char *str, char *input, int i, int flag);
t_export	*new_export(char *content, char *name);
void		export_add_back(t_export **list, t_export *newnode);
void		*export_clear(t_export **list, void (*del)(void *));

/**
 * functions from export
 */
void		swap_list(t_list **list, t_list *head);

/**
 * functions from cd
 */

void		*envp_cd_mod(char ***env, char *path, int type);
char		*ft_strlower(char *str);
char		*str_mod(char *cur, char *str, int i, int len);
char		*path_modify(char *cur, char *str);
int			get_pos_above_path(char *str);
char		*get_above_path(char *current);
void		error_cd(char *cmd);
char		*get_dest_path_wl_sign(char *cur, char *pwd, \
									char *input, t_data *data);
// char		*get_dest_path_wl_sign(char *cur, char *pwd, char *input);
char		*get_dest_path_env(t_data *data, char *envtype);
// char		*get_dest_path_env(char **env, char *envtype);
char		*obtain_pwd_home(t_data *data, int flag);
// char		*obtain_pwd_home(char **env, int flag);

/**
 * functions from utils
 */
int			av_amount(char **strs);
// int			check_valid(char *str, char *cmd);
int			check_valid(char *str, char *cmd, t_data *data);
char		*get_env(char **env, char *type);
/**
 * functions from utils
 */

void		error_av_built(char *cmd, char *av, char *comment);
void		error_id_built(char *cmd, char *av, char *comment);
void		error_built(char *cmd, char *comment);
int			error_notset(char *cmd, char *input);
void		heap_error(int flag);
void		**ptr_free(void **ptr);
/* void		*all_tmp_free(t_temp *temp); */
char		**strs_free(char **strs);
char		*my_free(void *ptr);

#endif
