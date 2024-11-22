/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec6.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eenassir <eenassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 10:47:44 by eenassir          #+#    #+#             */
/*   Updated: 2024/11/21 11:07:24 by eenassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_stat(const char *cmd)
{
	struct stat	state;

	if ((stat(cmd, &state) == 0) && ((cmd[0] == '.' && cmd[1] == '/') \
	|| cmd[0] == '/'))
	{
		if (S_ISDIR(state.st_mode))
			return (1);
		else if (S_ISREG(state.st_mode))
			return (2);
	}
	return (0);
}

void	ft_execv_error(char *cmd)
{
	int	status;

	if (!cmd)
		return ;
	status = ft_stat(cmd);
	if (status == 1)
		fd_print (2, cmd, ": is a directory\n", NULL);
	else if (status == 2)
		fd_print (2, cmd, ": Permission denied\n", NULL);
	else
		fd_print (2, cmd, ": command not found\n", NULL);
	if (status)
		exit(126);
	exit(127);
}
