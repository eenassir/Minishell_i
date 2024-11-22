/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eenassir <eenassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 09:45:01 by eenassir          #+#    #+#             */
/*   Updated: 2024/11/21 15:51:39 by eenassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_alloc_char(int cpt)
{
	char	**ptr;

	ptr = NULL;
	ptr = re_malloc(sizeof(char *) * (cpt + 1), NDS);
	if (!ptr)
		return (NULL);
	ptr[cpt] = NULL;
	return (ptr);
}

void	ft_get_cmdss(t_shell *scope, t_node **list, t_node_env *list_env)
{
	scope->cmd = ft_alloc_char(ft_count_cmd((*list)));
	scope->re = ft_alloc_char(ft_count_re((*list)));
	ft_put_args(list, scope->cmd, scope->re);
	ft_herdoc_geter(scope, list_env);
}

void	ft_buil1(int *t, t_shell *scope)
{
	(close (scope->fd[1]), close (scope->s[0]));
	if (scope->outfile != -1)
	{
		*t = dup(1);
		dup2(scope->outfile, 1);
	}
	else if (scope->count != scope->stop)
		dup2(scope->s[1], 1);
}

void	ft_buil2(int t, t_shell *scope)
{
	if (scope->stop == 0)
	{
		dup2(t, 1);
		close (scope->outfile);
	}
}

int	ft_builts(t_shell *scope, t_node_env *list)
{
	int	t;
	int	status;

	(1) && (t = -1, status = 0);
	ft_buil1(&t, scope);
	if (ft_strncmp(scope->cmd[0], "export", 6) == 0)
		status = ft_export(scope->cmd, list);
	if (ft_strncmp(scope->cmd[0], "unset", 5) == 0)
		status = ft_unset(scope->cmd, &list);
	else if (ft_strncmp(scope->cmd[0], "cd", 2) == 0)
		status = ft_cd(scope->cmd, list);
	else if (ft_strncmp(scope->cmd[0], "echo", 4) == 0)
		status = ft_echo(scope->cmd);
	else if (ft_strncmp(scope->cmd[0], "env", 3) == 0)
		status = ft_env(list);
	else if (ft_strncmp(scope->cmd[0], "pwd", 3) == 0)
		status = ft_pwd();
	if (ft_strncmp(scope->cmd[0], "exit", 4) == 0)
	{
		if (scope->stop == 0)
			write (1, "exit\n", 5);
		(ft_exit(scope->cmd), status = ft_exit_status(-1));
	}
	ft_buil2(t, scope);
	return (status);
}
