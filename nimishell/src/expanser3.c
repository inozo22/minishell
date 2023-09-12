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

//DELETE
#include "../lib/libft/libft.h"

volatile int	g_return_val = 0;

char	*get_var_value(char *env_var, char *envp[], int len)
{
	int	i;

//	printf("\n\nenv var: %s len: %d\n", env_var, len);
	i = -1;
	while (envp[++i])
	{
//		printf("pos of = : %c, envp[%d]: %s\n", envp[i][len], i, envp[i]);
		if (!ft_strncmp(env_var + 1, envp[i], len) && envp[i][len] == '=')
			return (ft_strdup(envp[i] + len + 1));
	}
	ft_printf("minishell: %s: Undefined variable.\n", env_var);
	return (NULL);
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
char	*is_expand(char *env_var, int len, char *env[])
{
	//GET PID FROM DATA
	int	pid;

	pid = 123;	
	if (!ft_strncmp(env_var, "$?", len))
	{
		return (ft_itoa(g_return_val));
	}
	if (!ft_strncmp(env_var, "$!", len))
		return (ft_itoa(g_return_val));
	if (!ft_strncmp(env_var, "$$", len))
		return (ft_itoa(pid));
	if (!ft_strncmp(env_var, "$-", len))
		return (ft_strdup("himBH"));
	if (!ft_strncmp(env_var, "$@", len) || !ft_strncmp(env_var, "$*", len))
		return (ft_strdup(""));
	if (!ft_strncmp(env_var, "$#", len))
		return (ft_itoa(0));
	//keep opening the input if I put "minishell", at this moment put a space at the end of the string to escape
	if (!ft_strncmp(env_var, "$0", len))
		return (ft_strdup("minishell "));
	if (!ft_strncmp(env_var, "$IFS", len))
		return (ft_strdup("\t\n"));
	if (ft_isdigit(env_var[1]))
	{
//		printf("%sLine: %d HERE I AM%s\n", COLOR_RED, __LINE__, COLOR_RESET);
		return (ft_strdup(""));
	}
	if (!(env_var[1]) || (!ft_isalnum(env_var[1]) && env_var[1] != '_'))
	{
//		printf("%sLine: %d HERE I AM%s\n", COLOR_RED, __LINE__, COLOR_RESET);
		return (NULL);
	}
	return(get_var_value(env_var, env, len));
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


/**
 * @note i[0] i
 * @note i[1] j
 * @note i[2] len
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
	//copy 
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
 * @note pieces[0] before $
 * @note pieces[1] expanded var
 * @note pieces[2] after var 
 */
int	expand(char **str, int *pos, int quotes, char *env[])
{
	int		i[2];
	char	*tmp;
	char	*pieces[3];

	ft_bzero(i, 2 * sizeof(int));
	i[0] = *pos;
	tmp = *str;
	if (ft_isdigit(*str[*pos + 1]))
		i[0]++;
	else
		while ((*str)[i[0]] && (*str)[i[0]] != ' ' && (*str)[i[0]] != quotes)
			i[0]++;
	pieces[1] = is_expand(&tmp[*pos], i[0] - *pos, env);
	if (!pieces[1])
		return (0);
	ft_printf("pieces[1]: %s\n", pieces[1]);
	pieces[0] = ft_substr(tmp, 0, *pos);
	ft_printf("pieces[0]: %s\n", pieces[0]);
	pieces[2] = ft_substr(tmp, i[0], ft_strlen(tmp) - i[0]);
	ft_printf("pieces[2]: %s\n", pieces[2]);
	if (!pieces[0] || !pieces[1] || !pieces[2])
	{
		while (i[1] < 3)
			free(pieces[i[1]++]);
		return (1);
	}
	free(*str);
	*str = ft_strjoin_many(3, pieces[0], pieces[1], pieces[2]);
	if (*str)
		return (1);
	return (0);
}

/**
 * @param pos[2] to keep and free string 
 */
char	*expanser(char *str, char *env[])
{
	int	i;
	int quotes;

	i = -1;
	while (str[++i])
	{
		ft_printf("i: %d\n", i);
		quotes = is_quote(str[i]);
		if (str[i] == '$' && quotes != '\'')
		{
			ft_printf("quotes status: %d\n", quotes);
			ft_printf("str pos: %s\n", str + i);	
			if (expand(&str, &i, quotes, env))
				return (NULL);
		}
	}
	return (str);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*str;
	char	*expanded;
	int		i = 0;

	if (argc != 2)
		return (1);
	while (argv[++i])
	{
		ft_printf("Expanding %s\n", argv[i]);
		str = ft_strdup(argv[i]);
		expanded = expanser(str, envp);
		printf("expanded: %s\n", expanded);
		free(str);
	}
	return (0);
}

// cc -Wall -Wextra -g3 -fsanitize=address -Ilib/libft -Iinclude src/expanser3.c src/lexer.c lib/libft/libft.a && ./a.out "'$HOME': $HOME		'$USER':\"$USER\"		$PWD		'$OLDPWD':$OLDPWD		$INVENT:\"$INVENT\"		\"$?\"		'$-':\"S-\"		'S0':\"$0\""

// cc -Wall -Wextra -g3 -Ilib/libft -Iinclude src/expanser3.c src/lexer.c lib/libft/libft.a && valgrind --leak-check=full ./a.out "'$HOME': $HOME          '$USER':\"$USER\"                $PWD            '$OLDPWD':$OLDPWD               $INVENT:\"$INVENT\"              \"$?\"          '$-':\"S-\"             'S0':\"$0\""
