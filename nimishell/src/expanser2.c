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
	int	i;

	printf("\n\nenv var: %s len: %d\n", env_var, len);
	i = -1;
	while (envp[++i])
	{
		printf("pos of = : %c, envp[%d]: %s\n", envp[i][len], i, envp[i]);
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
	{
		return (ft_itoa(data->return_val));
	}
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
	printf("%sLine: %d HERE I AM%s\n", COLOR_RED, __LINE__, COLOR_RESET);
	return(get_var_value(token, envp, len));
}

/**
 * @brief get the full string from env
 * @return when there is value return full value, otherwise null
 */
// char	*expand(char *arg, int start, int end, char *var_value, char *envp[])
// {
// 	char	*ret;
// 	int		i;
// 	int		len;

// 	(void)var_value;
// 	ret = NULL;
// 	printf("%sstart: %d, end: %d, arg: %s%s\n", COLOR_RED, start, end, arg, COLOR_RESET);
// 	i = -1;
// 	len = ft_strlen(&arg[1]);
// 	while (envp[++i])
// 	{
// 		if (!ft_strncmp(&arg[1], envp[i], len) && envp[i][len] == '=')
// 			break ;
// 	}
// 	if (envp[i])
// 	{
// 		ret = (char *)ft_calloc(ft_strlen(envp[i]) - len, 1);
// 		if (!ret)
// 			return (NULL);//memory allocate error
// 		ft_strcpy(ret, &envp[i][len + 1]);
// //		printf("%sret :%s%s\n", COLOR_RED, ret, COLOR_RESET);
// 	}
// 	return (ret);
// }

/**
 * @param pos[2] to keep and free string 
 */
char	*expanser(char *arg, char *envp[], t_data *data)
{
	char	*expanded;
	char	*tmp;
	char	*pos[3];

	expanded = ft_strdup(arg);
	pos[2] = ft_strdup(expanded);
	pos[0] = ft_strchr(pos[2], '$');
	while (pos[0] && arg[0] != '\'' && ft_strlen(pos[0]))
	{
		pos[1] = pos[0] + 1;
		while (ft_isalnum(*pos[1]))
			pos[1]++;
		if (*pos[0] == '$')
			tmp = is_expand(pos[0], (pos[1] - pos[0]- 1), envp, data);
		else
			tmp = ft_strdup(pos[0]);
		if (tmp)
		{
			if (ft_strcmp(expanded, arg) != 0)
				expanded = ft_strjoin(expanded, tmp);
			else
			{
				free (expanded);
				expanded = ft_calloc(ft_strlen(tmp), 1);
				ft_strcpy(expanded, tmp);
			}
			free(tmp);
		}
		else if (!tmp && ft_strcmp(expanded, arg) == 0)
		{
			free(expanded);
			expanded = NULL;
		}
		if (pos[1] - pos[0] == 1)
			pos[1]++;
		pos[0] = pos[1];
	}




//今ここ


/* 	if (*expanded == '\'' || *expanded == '\"')
		expanded = remove_quotes(expanded); */
	return (free (pos[2]), expanded);
}
