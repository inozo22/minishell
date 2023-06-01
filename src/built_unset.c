/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 09:50:35 by nimai             #+#    #+#             */
/*   Updated: 2023/06/01 13:22:12 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief temporary error management
 * @author nimai
 * @note when decided error management, merge it.
 */
void	error_unset(char *cmd, char *comment)
{
	ft_printf("minishell: unset: `%s': %s\n", cmd, comment);
}

/**
 * @brief string checker.
 * @author nimai
 * @return 1 if it's valid, otherwise 0.
 * @note doesn't work, CHECK
 */
int	check_valid(char *str)
{
	int	i;

	i = 0;
	if (!(ft_isalpha(str[i]) || str[i] == '_'))
	{
		error_unset(str, "not a valid identifier");
		return (0);
	}
	while (str[++i])
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
		{
			error_unset(str, "not a valid identifier");
			return (0);
		}
	}
	return (1);
}

/**
 * @brief manage "builtin" unset cmd.
 * @author nimai
 * @param **av "unset", "ABC", "DEF"
 * @note how to delete a variable??? 
 */
t_temp	*unset_env(t_temp *temp, char *str)
{
	int		i;
	int		len;
	char	**env;

	i = 0;
	env = (char **)temp->envp;
	while (env[i])
	{
		len = 0;
		while (env[i][len] != '=' && env[i][len])
			len++;
		if (ft_strncmp(str, env[i], ft_strlen(str)) == 0 && \
		ft_strncmp(str, env[i], len) == 0)
		{
			env[i] = NULL;
		}
		printf("env[%d]: %s\n", i, env[i]);
		i++;
	}
	exit (1);
	temp->envp = NULL;
	temp->envp = env;
	return (temp);
}

/**
 * @brief manage "builtin" unset cmd.
 * @author nimai
 * @param **av "unset", "ABC", "DEF"
 * @return 
 */
int	built_unset(t_temp *temp)
{
	int		i;
	char	**av;

	av = (char **)temp->argv;
	i = 2;
	while (av[i])
	{
//		printf("Line: %d\n", __LINE__);
		if (check_valid(av[i]) == 1)
			temp = unset_env(temp, av[i]);
		i++;
//		printf("Line: %d\n", __LINE__);
	}
//	printf("Line: %d\n", __LINE__);
	printf("\n		===TEST ENV===\n");
	built_env(temp);
	printf("		===TEST ENV===\n");
	return (0);
}

/**
 * BEHAVIOUR IN BASH
 * when execute env, the list is not ordered 
 * 
 * 
 * MEMORY LEAKS
 * 230526nimai: When I try free it, receive errors say that I'm trying free memory which is not allocated.
 * But yes, allocated.
 * 
 * 
 * 230601nimai: 
 * env[0]: SECURITYSESSIONID=186f0
env[1]: USER=nimai
env[2]: MallocNanoZone=0
env[3]: COMMAND_MODE=unix2003
env[4]: PATH=/Users/nimai/.docker/bin:/Users/nimai/.brew/bin:/Users/nimai/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Users/nimai/.docker/bin:/Users/nimai/.brew/bin
env[5]: HOME=/Users/nimai
env[6]: SHELL=/bin/zsh
env[7]: LaunchInstanceID=171267E8-A52B-4732-BA65-0F40CC1DB70C
env[8]: __CF_USER_TEXT_ENCODING=0x18D31:0x0:0x0
env[9]: XPC_SERVICE_NAME=0
env[10]: SSH_AUTH_SOCK=/private/tmp/com.apple.launchd.RUQ9jkhj6S/Listeners
env[11]: XPC_FLAGS=0x0
env[12]: LOGNAME=nimai
env[13]: TMPDIR=/var/folders/zz/zyxvpxvq6csfxvn_n000cd6400339j/T/
env[14]: ORIGINAL_XDG_CURRENT_DESKTOP=undefined
env[15]: SHLVL=1
env[16]: PWD=/Users/nimai/42/42cursus/minishell
env[17]: OLDPWD=/Users/nimai/42/42cursus/minishell
env[18]: ZSH=/Users/nimai/.oh-my-zsh
env[19]: PAGER=less
env[20]: (null)
env[21]: LSCOLORS=Gxfxcxdxbxegedabagacad
env[22]: LS_COLORS=di=1;36:ln=35:so=32:pi=33:ex=31:bd=34;46:cd=34;43:su=30;41:sg=30;46:tw=30;42:ow=30;43
env[23]: HOMEBREW_CACHE=/tmp/nimai/Homebrew/Caches
env[24]: HOMEBREW_TEMP=/tmp/nimai/Homebrew/Temp
env[25]: TERM_PROGRAM=vscode
env[26]: TERM_PROGRAM_VERSION=1.78.0
env[27]: LANG=en_US.UTF-8
env[28]: COLORTERM=truecolor
env[29]: GIT_ASKPASS=/Applications/Visual Studio Code.app/Contents/Resources/app/extensions/git/dist/askpass.sh
env[30]: VSCODE_GIT_ASKPASS_NODE=/Applications/Visual Studio Code.app/Contents/Frameworks/Code Helper (Plugin).app/Contents/MacOS/Code Helper (Plugin)
env[31]: VSCODE_GIT_ASKPASS_EXTRA_ARGS=--ms-enable-electron-run-as-node
env[32]: VSCODE_GIT_ASKPASS_MAIN=/Applications/Visual Studio Code.app/Contents/Resources/app/extensions/git/dist/askpass-main.js
env[33]: VSCODE_GIT_IPC_HANDLE=/var/folders/zz/zyxvpxvq6csfxvn_n000cd6400339j/T/vscode-git-06b3d0b2cf.sock
env[34]: VSCODE_INJECTION=1
env[35]: ZDOTDIR=/Users/nimai
env[36]: USER_ZDOTDIR=/Users/nimai
env[37]: TERM=xterm-256color
env[38]: _=/Users/nimai/42/42cursus/minishell/./minishell
 * 
 * 
 */
