/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanser2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 10:32:20 by nimai             #+#    #+#             */
/*   Updated: 2023/08/10 10:32:20 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../lib/libft/libft.h"

char	*get_var_value(char *env_var, char *envp[], int len)
{
	int		i;
//	int		j;
//	char	*tmp;

	printf("\n\nenv var: %s len: %d\n", env_var, len);
	i = -1;
	// j = 0;
	// if (!ft_strncmp(env_var, "${", 2))
	// {
	// 	tmp = ft_calloc(len, 1);
	// 	while (env_var[++i] != '}')
	// 	{
	// 		if (env_var[i] != '{')
	// 			tmp[j++] = env_var[i];

	// 	}
	// 	tmp[j] = 0;
	// 	len = j - 1;
	// 	ft_strcpy(env_var, tmp);
	// 	free (tmp);
	// }
	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(env_var + 1, envp[i], len) && envp[i][len] == '=')
		{
			return (ft_strdup(envp[i] + len + 1));
		}
	}
	if (!envp[i])
		return (NULL);
	return (ft_substr(env_var, 0, len));
}

//$- returns a string representing the flags of the shell
//$@ $< and $> not implemented, return empty
/**
 * @brief expands considering the special parameters in bash
 * @author bde-mada
 * @note ($*) Expands to the positional parameters, starting from one.
 * @note ($@) Expands to the positional parameters, starting from one.
 * @note ($#) Expands to the number of positional parameters in decimal.
 * @note ($?) Expands to the exit status of the most recently executed 
 * foreground pipeline.
 * @note ($-) Expands to the current option flags as specified upon invocation,
 * by the set builtin command, or those set by the shell itself.
 * @note ($$) Expands to the process ID of the shell. In a subshell, it expands
 * to the process ID of the invoking shell, not the subshell.
 * @note ($!) Expands to the process ID of the job most recently placed into
 * the background
 * @note ($0) Expands to the name of the shell or shell script.
 * @note ($$) Expands to the pid of the current shell.
 * @note ($1-9) Expands to the corresponding arguments passed to bash
 */
char	*is_expand(char *token, int len, char *envp[], t_data *data)
{
	if (!ft_strncmp(token, "$?", 2))
		return (ft_itoa(data->return_val));
	if (!ft_strncmp(token, "$!", 2))
		return (ft_itoa(data->return_val));
	if (!ft_strncmp(token, "$$", 2))
		return (ft_itoa(data->pid));
	if (!ft_strncmp(token, "$-", 2))
		return (ft_strdup("himBH"));
	if (!ft_strncmp(token, "$@", 2) || !ft_strncmp(token, "$*", 2))
		return (ft_strdup(""));
	if (!ft_strncmp(token, "$#", 2))
		return (ft_itoa(0));
	//keep opening the input if I put "minishell", at this moment put a space at the end of the string to escape
	if (!ft_strncmp(token, "$0", 2))
		return (ft_strdup("minishell "));
	// if (!ft_strncmp(token, "${", 2))
	// 	return (get_var_value(token, envp, len));
	if (!ft_strncmp(token, "$IFS", 4))
		return (ft_strdup("\t\n"));
	if (ft_isdigit(token[1]))
	{
		printf("%sLine: %d HERE I AM%s\n", COLOR_RED, __LINE__, COLOR_RESET);
		return (ft_strdup(""));
	}
	if (!(token[1]) || (!ft_isalnum(token[1]) && token[1] != '_'))
	{
		printf("%sLine: %d HERE I AM%s\n", COLOR_RED, __LINE__, COLOR_RESET);
		return (NULL);
	}
	return(get_var_value(token, envp, len));
}

char	*obtain_expanded(char *tmp, char *ret, char *arg)
{
	if (ft_strcmp(ret, arg) != 0)
		ret = ft_strjoin(ret, tmp);
	else
	{
		free (ret);
		ret = ft_calloc(ft_strlen(tmp), 1);
		ft_strcpy(ret, tmp);
	}
	return (ret);
}

char	*expand(char *pos[3], char *arg, t_data *data, char *expanded)
{
	char	*tmp;
	int		flag;

	flag = 0;
	if ((*pos[0]) == '\'')
		flag++;
	while (ft_isalnum(*pos[1]) || (*pos[1] == '$' && flag) || \
	(*pos[1] - 1 == '$' && *pos[1] == '{'))
		pos[1]++;
	// if (*pos[1] == '}')
	// 	pos[1]++;
	// if (*pos[1] == '\'' && flag)
	// {
	// 	pos[1]++;
	// 	tmp = ft_strndup(pos[0], (pos[1] - pos[0]));
	// }
	if (/* *pos[1] == '}' ||  */(*pos[1] == '\'' && flag))
		pos[1]++;
		if (*pos[1] == '\'' && flag)
			tmp = ft_strndup(pos[0], (pos[1] - pos[0]));
	if (*pos[0] == '$')//it will not enter with single quote
		tmp = is_expand(pos[0], (pos[1] - pos[0]- 1), data->env, data);
	else
		tmp = ft_strndup(pos[0], (pos[1] - pos[0]));
	if (tmp)
		expanded = obtain_expanded(tmp, expanded, arg);
	else if (!tmp && ft_strcmp(expanded, arg) == 0)
		return (free (expanded), NULL);
	return (free (tmp), expanded);
}

/**
 * @note i[0] i
 * @note i[1] j
 * @note i[2] len
 * 
 * 
 * 
  */
char	*remove_quotes(char *str)
{
	char	*ret;
	int		i[3];

	ft_bzero(i, 3 * sizeof(int));
	ret = NULL;
	while (str[i[0]])
	{
		if (str[i[0]] != '\'' && str[i[0]] != '\"')
			i[2]++;
		i[0]++;
	}
	ret = ft_calloc(i[2] + 1, 1);
	if (!ret)
		return (NULL);//malloc error
	i[0] = -1;
	//copy string
	while (++i[0] <= i[2] + 1)
	{
		if (str[i[0]] != '\'' && str[i[0]] != '\"')
		{
			ret[i[1]] = str[i[0]];
			i[1]++;
		}
	}
	// if (!ret)
	// 	return (str);
	return (ret);
}

/**
 * @param pos[2] to keep and free string 
 */
char	*expanser(t_list *list, t_data *data)
{
	char	*expanded;
	char	*pos[3];

	expanded = ft_strdup(list->content);
	pos[2] = ft_strdup(expanded);
	pos[0] = ft_strchr(pos[2], '$');
	// if (pos[0])
	// 	printf("len: %ld\n", ft_strlen(pos[0]));
	while (pos[0] && list->content[0] != '\'' && ft_strlen(pos[0]))
	{
		pos[1] = pos[0] + 1;
//		printf("expanded before expand: %s pos[0]: %s\n", expanded, pos[0]);
		expanded = expand(pos, list->content, data, expanded);
//		printf("expanded after expand: %s\n", expanded);
		printf("Line: %d pos[1]: %s pos[0]: %s\n", __LINE__, pos[1], pos[0]);
		if (!pos[0]/*  || !pos[1] */)
			break ;
		if (pos[1] - pos[0] == 1)
			pos[1]++;
		pos[0] = pos[1];
	}
//	printf("expanded: %s\n", expanded);
	expanded = remove_quotes(expanded);
	return (free (pos[2]), expanded);
}

		// if (pos[1] - pos[0] == 1 && *pos[0] + 1 != '{')
		// 	pos[1]++;
		// else
		// 	while(*pos[1] != '}')
		// 	{
		// 		pos[1]++;
		// 	}
