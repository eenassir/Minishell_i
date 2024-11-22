/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eenassir <eenassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 09:38:02 by eenassir          #+#    #+#             */
/*   Updated: 2024/11/21 10:55:16 by eenassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_get_path(t_shell *scope)
{
	char	**paths;
	int		i;

	i = 0;
	paths = NULL;
	while (scope->envp[i] && ft_strncmp(scope->envp[i], "PATH=", 4) != 0)
		i++;
	if (scope->envp[i] != NULL)
	{
		paths = ft_split(scope->envp[i] + 5, ':');
		if (!paths)
			return (NULL);
	}
	return (paths);
}

int	ft_exe_cmds(t_shell *scope)
{
	char	*tmp;
	char	**paths;
	int		i;
	char	*var;

	tmp = NULL;
	var = NULL;
	i = -1;
	paths = ft_get_path(scope);
	tmp = ft_gstrdup(scope->cmd[0]);
	if (tmp && tmp[0] != '/')
		tmp = ft_gstrjoin("/", tmp);
	if (paths != NULL)
	{
		while (paths[++i])
		{
			var = ft_gstrjoin(paths[i], tmp);
			if (access(var, X_OK) == 0)
				break ;
		}
	}
	(tmp = ft_gstrdup(var));
	if (access(tmp, X_OK) == 0)
		(scope->cmd[0] = ft_gstrdup(tmp));
	return (0);
}
