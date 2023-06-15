/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 09:50:35 by nimai             #+#    #+#             */
/*   Updated: 2023/06/15 11:32:09 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief manage "builtin" unset cmd.
 * @author nimai
 * @param **av "unset", "ABC", "DEF"
 * @note how to delete a variable??? 
 */
t_data	*unset_env(t_data *data, char *str)
{
	int		i;
	int		j;
	char	**tmp;

	i = -1;
	j = -1;
	tmp = (char **)malloc(sizeof(char *) * (av_amount(data->env) + 1));
	if (!tmp)
		return (NULL);
	while (data->env[++i])
	{
		if (ft_strncmp(data->env[i], str, ft_strlen(str)) || \
		ft_strncmp(str, data->env[i], ft_strlen(str)))
		{
			tmp[++j] = data->env[i];
		}
		data->env[i] = NULL;
	}
	free (data->env);
	data->env = tmp;
	return (data);
}

/**
 * @brief manage "builtin" unset cmd.
 * @author nimai
 * @param **av "unset", "ABC", "DEF"
 * @note if it's not valid, receive error message, but if it's valid and doesn't exist will not receive anything
 */
int	built_unset(char **input, t_data *data)
{
	int		i;

	i = 1;
	while (input[i])
	{
		if (check_valid(input[i], "unset") == 1)
			data = unset_env(data, input[i]);
		i++;
	}
	return (0);
}

/**
 * BEHAVIOUR IN BASH
 * when execute env, the list is not ordered 
 * 
 * 
 * 
 * 230601nimai: 
 * unset: kind of did it, but should be started over after it've been decided on the structure."
[main b02d1eb] unset: kind of did it, but should be started over after it've been decided on the structure
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
env[20]: (null) <= as I have null here, will not move to next when I print it
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
