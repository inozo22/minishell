/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 18:20:12 by nimai             #+#    #+#             */
/*   Updated: 2023/05/17 12:53:26 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

typedef struct s_var
{
	const char		*key;
	const char		*value;
	bool			is_shell_var;
	struct s_var	*next;	
}	t_var;

//env.c
/**
 * @brief obtain env.
 * @return current position of t_var.
 */
t_var	*get_env(const char *env_key);

//env_setter.c
/**
 * @brief obtain value and count the depth.
 * @return when it has problem returns -1, otherwise 0.
 */
int		ft_setenv(const char *key, const char *value, bool is_shell_var);


/* void	free_vars(t_var *vars);
t_var	*add_new_var(t_var **vars,
			const char *key, const char *value, bool is_shell_var);
t_var	*kvstr2var(char *kvstr, bool is_shell_var);
t_var	*environ2vars(char **environ);
char	**vars2environ(t_var *vars);

t_var	*get_env(const char *env_key);
char	*get_env_val(const char *env_key);
char	**split_first_c(const char *str, char c);
char	**get_colon_units(const char *str, const char *default_str);
char	*generate_kvstr(const char *key, const char *value);
char	*get_val_from_kvstr(const char *kvstr, char delimiter);
int		ft_setenv(const char *key, const char *value, bool is_shell_var);
int		ft_unsetenv(const char *key);

// Expander (exp)
bool	exp_join_str_or_env(char **result,
			char **str, int *len, bool *is_in_env);
bool	exp_will_toggle_env(bool is_in_env,
			bool is_in_noexpand, char *str, int len);
char	*exp_result_join_normal_str(char *result,
			char *str, int len);
char	*exp_expand_env_and_join(char *result,
			char *str, int env_len);
char	*expand_env_var(char *str);

// Utilities for command exit code.
int		get_status(void);
void	set_status(int status_value);
int		set_status_and_ret(int status_value, int ret_value); */




#endif