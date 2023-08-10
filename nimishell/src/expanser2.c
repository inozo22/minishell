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
#include <stdio.h>

char	*get_var_value(char *env_var, char *envp[], int len)
{
	int	i;
//	int	len;

	printf("\n\nenv var: %s len: %d\n", env_var, len);
	i = -1;
//	len = ft_strlen(env_var) - 1;
	while (envp[++i])
	{
		printf("pos of = : %c, envp[%d]: %s\n", envp[i][len], i, envp[i]);
		if (!ft_strncmp(env_var + 1, envp[i], len) && envp[i][len] == '=')
		{
			printf("%sLine: %d HERE I AM%s\n", COLOR_RED, __LINE__, COLOR_RESET);
			return (ft_strdup(envp[i] + len + 1));
		}
	}
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
/* 	int	i;

	i = -1; */
	printf("%sHERE I AM%s\n", COLOR_RED, COLOR_RESET);
	if (!ft_strncmp(token, "$?", 2))
	{
		printf("%sLine: %d HERE I AM%s\n", COLOR_RED, __LINE__, COLOR_RESET);
		return (ft_itoa(data->return_val));
	}
	if (!ft_strncmp(token, "$!", 2))
	{
		printf("%sLine: %d HERE I AM%s\n", COLOR_RED, __LINE__, COLOR_RESET);
		return (ft_itoa(data->return_val));
	}
	if (!ft_strncmp(token, "$$", 2))
	{
		printf("%sLine: %d HERE I AM%s\n", COLOR_RED, __LINE__, COLOR_RESET);
		return (ft_itoa(data->pid));
	}
	if (!ft_strncmp(token, "$-", 2))
	{
		printf("%sLine: %d HERE I AM%s\n", COLOR_RED, __LINE__, COLOR_RESET);
		return ("himBH");
	}
	if (!ft_strncmp(token, "$@", 2) || !ft_strncmp(token, "$*", 2))
	{
		printf("%sLine: %d HERE I AM%s\n", COLOR_RED, __LINE__, COLOR_RESET);
		return ("");
	}
	if (!ft_strncmp(token, "$#", 2))
	{
		printf("%sLine: %d HERE I AM%s\n", COLOR_RED, __LINE__, COLOR_RESET);
		return ("0");
	}
	if (!ft_strncmp(token, "$IFS", 4))
	{
		printf("%sLine: %d HERE I AM%s\n", COLOR_RED, __LINE__, COLOR_RESET);
		return ("\t\n");
	}
	if (ft_isdigit(token[1]))
	{
		printf("%sLine: %d HERE I AM%s\n", COLOR_RED, __LINE__, COLOR_RESET);
		return ("");
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
char	*expand(char *arg, int start, int end, char *var_value, char *envp[])
{
	char	*ret;
	int		i;
	int		len;

	(void)var_value;
	ret = NULL;
	printf("%sstart: %d, end: %d, arg: %s%s\n", COLOR_RED, start, end, arg, COLOR_RESET);
	i = -1;
	len = ft_strlen(&arg[1]);
	while (envp[++i])
	{
		if (!ft_strncmp(&arg[1], envp[i], len) && envp[i][len] == '=')
			break ;
	}
	if (envp[i])
	{
		ret = (char *)ft_calloc(ft_strlen(envp[i]) - len, 1);
		if (!ret)
			return (NULL);//memory allocate error
		ft_strcpy(ret, &envp[i][len + 1]);
//		printf("%sret :%s%s\n", COLOR_RED, ret, COLOR_RESET);
	}
	return (ret);
}
// char	*expand(char *arg, int start, int end, char *var_value)
// {
// 	char	*expanded;
// 	char	*tmp;

// 	expanded = ft_substr(arg, 0, start);
// 	printf("First section: %s\n", expanded);
// 	tmp = expanded;
// 	expanded = ft_strjoin(expanded, var_value);
// 	printf("First section + expanded: %s\n", expanded);
// 	free(tmp);
// 	tmp = expanded;
// 	expanded = ft_strjoin(expanded, arg + end);
// 	free(tmp);
// 	printf("All: %s\n", expanded);
// 	return (expanded);
// }


char	*expanser(char *arg, char *envp[], t_data *data)
{
	char	*expanded;
//	char	*var_value;
	char	*tmp;
	//int		i;
	char 	*pos[2];

	//i = 0;//changed from -1
	expanded = ft_strdup(arg);
	pos[0] = ft_strdup(expanded);
	pos[0] = ft_strchr(pos[0], '$');
	//if there is no "$", never enter
	while (pos[0] && arg[0] != '\'' && ft_strlen(pos[0]))
	{
		printf("%sexpanser len: %zu, pos[0]: %s%s\n", COLOR_RED, ft_strlen(pos[0]), pos[0], COLOR_RESET);
		pos[1] = pos[0] + 1;
		while (ft_isalnum(*pos[1])/*  || *pos[1] == '$' */)
			pos[1]++;
		// if (*pos[1] == '$')
		// 	pos[1]++;
		printf("pos[1]: %s\n", pos[1]);
		tmp = is_expand(pos[0], pos[1] - pos[0]- 1, envp, data);
		printf("%sAfter expand tmp: %s pos[1] - pos[0]: %ld%s\n", COLOR_RED, tmp, pos[1] - pos[0], COLOR_RESET);
		if (ft_strcmp(expanded, arg) != 0)
			expanded = ft_strjoin(expanded, tmp);
		else
		{
			printf("%sLine: %d HERE I AM%s\n", COLOR_RED, __LINE__, COLOR_RESET);
			free (expanded);
			expanded = ft_calloc(ft_strlen(tmp), 1);
			ft_strcpy(expanded, tmp);
		}
		free(tmp);
		printf("expanded: %s\n", expanded);
		//pos[0] += pos[1] - pos[0] + 1;
		pos[0] = pos[1];
		// if (!ft_isalnum(pos[1][1]))
		// 	pos[0]++;
		printf("After move pos[0]: %s, len: %zu\n", pos[0], ft_strlen(pos[0]));
		// if (!ft_strlen(pos[0]))
		// 	break ;
	}
	/**
	 * @note int i is not necesarry
	 */
	return (expanded);
}
// 		printf("pos[0]: %d\n", *pos[0]);
// 		printf("%sI will expand: %s, pos[0]: %s%s\n", COLOR_RED, expanded, pos[0], COLOR_RESET);
// 		pos[1] = pos[0] + 1;
// 		while (ft_isalnum(*pos[1]))
// 			pos[1]++;
// 		printf("start: %s, end: %s\n", pos[0], pos[1]);
// 		tmp = ft_strdup(expanded);
// 		printf("Line: %d, tmp: %s expanded: %s\n", __LINE__, tmp, expanded);
// 		free (expanded);
// 		var_value = is_expand(pos[0], envp, data);//check unique letter
// 		while (*var_value)
// 		{
// 			printf("%c", *var_value);
// 			var_value++;
// 		}
// 		write(1, "\n", 1);
// //		printf("var value: %s, var value[0]: %d\n", var_value, var_value[0]);
// 		if (!var_value)
// 		{
// 			var_value = expand(expanded, pos[0] - expanded, pos[1] - pos[0], var_value, envp);
// 		}
// 		expanded = (char *)ft_calloc(ft_strlen(var_value) + ft_strlen(tmp) + 1, 1);
// 		ft_strcpy(expanded, tmp);
// 		ft_strcat(expanded, var_value);
// 		printf("Line: %d, tmp: %s expanded: %s\n", __LINE__, tmp, expanded);
// 	//	printf("i val: %d, i pos after write: %s\n",i, arg + i);
// 		if (pos[0][0] == '$')
// 			free(var_value);
// 		free (tmp);
// 		pos[0] += pos[1] - pos[0] + 1;
// 		printf("%spos[0]: %s%s\n", COLOR_RED, pos[0], COLOR_RESET);

// char	*expanser(char *arg, char *envp[], t_data *data)
// {
// 	char	*expanded;
// 	char	*var_value;
// 	char	*tmp;
// 	//int		i;
// 	char 	*pos[2];

// 	//i = 0;//changed from -1
// 	expanded = ft_strdup(arg);
// 	pos[0] = ft_strchr(expanded, '$');
// 	//if there is no "$", never enter
// 	while (pos[0] && arg[0] != '\'')
// 	{
// 		printf("%sI will expand: %s, pos[0]: %s%s\n", COLOR_RED, expanded, pos[0], COLOR_RESET);
// 		pos[1] = pos[0] + 1;
// 		while (ft_isalnum(*pos[1]))
// 			pos[1]++;
// 		printf("start: %s, end: %s\n", pos[0], pos[1]);
// 		tmp = ft_strdup(expanded);
// 		printf("Line: %d, tmp: %s expanded: %s\n", __LINE__, tmp, expanded);
// 		free (expanded);
// 		var_value = is_expand(pos[0], envp, data);//check unique letter
// 		while (*var_value)
// 		{
// 			printf("%c", *var_value);
// 			var_value++;
// 		}
// 		write(1, "\n", 1);
// //		printf("var value: %s, var value[0]: %d\n", var_value, var_value[0]);
// 		if (!var_value)
// 		{
// 			var_value = expand(expanded, pos[0] - expanded, pos[1] - pos[0], var_value, envp);
// 		}
// 		expanded = (char *)ft_calloc(ft_strlen(var_value) + ft_strlen(tmp) + 1, 1);
// 		ft_strcpy(expanded, tmp);
// 		ft_strcat(expanded, var_value);
// 		printf("Line: %d, tmp: %s expanded: %s\n", __LINE__, tmp, expanded);
// 	//	printf("i val: %d, i pos after write: %s\n",i, arg + i);
// 		if (pos[0][0] == '$')
// 			free(var_value);
// 		free (tmp);
// 		pos[0] += pos[1] - pos[0] + 1;
// 		printf("%spos[0]: %s%s\n", COLOR_RED, pos[0], COLOR_RESET);
// 	}
// 	/**
// 	 * @note int i is not necesarry
// 	 */
// 	return (expanded);
// }
//230810nimai: expanded should be the whole string for the parm arg

/* int	main(int argc, char *argv[], char *envp[])
{
	char	*arg = "$SHELL first to expand SHELL, to expand 2 USER together: $USER$USER to expand HOME: $HOME, notexisting: $NONEXISTING";
	char	*expanded;
//	int		i = -1;

	expanded = NULL;
	if (argc != 1 && !*argv)
		return (1);
// 	while (envp[++i])
//		printf("%s\n", envp[i]);
//	printf("\n\n");
// 	expanded = get_var_value("USER", 4, envp);
	expanded = expanser(arg, envp);
	printf("expanded str: %s\n", expanded); 
	free (expanded);
	return (0);
}
 */
