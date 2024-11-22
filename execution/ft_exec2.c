/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eenassir <eenassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 09:30:59 by eenassir          #+#    #+#             */
/*   Updated: 2024/11/21 15:51:29 by eenassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_get_env(t_node_env *new_env)
{
	char	**ptr;
	char	*temp;
	int		i;

	i = 0;
	temp = NULL;
	ptr = NULL;
	ptr = (char **)re_malloc(sizeof(char *) * \
	(ft_count_env(new_env) + 1), NDS);
	if (!ptr)
		return (NULL);
	while (new_env)
	{
		if (new_env->key != NULL)
		{
			temp = ft_gstrjoin(new_env->key, "=");
			ptr[i] = ft_gstrjoin(temp, new_env->val);
			i++;
		}
		new_env = new_env->next;
	}
	ptr[i] = NULL;
	return (ptr);
}

int	ft_bool(char **ptr)
{
	if (ft_strncmp(ptr[0], "cd", 2) == 0 || \
	ft_strncmp(ptr[0], "env", 3) == 0 || \
	ft_strncmp(ptr[0], "pwd", 3) == 0 || \
	ft_strncmp(ptr[0], "unset", 5) == 0 || \
	ft_strncmp(ptr[0], "export", 6) == 0 || \
	ft_strncmp(ptr[0], "echo", 4) == 0 || \
	ft_strncmp(ptr[0], "exit", 4) == 0)
		return (1);
	return (0);
}

int	ft_exe_builts(t_shell *scope, t_node_env *list_env)
{
	int	id;

	id = -1;
	if (scope->stop != 0)
	{
		id = fork();
		if (id == -1)
		{
			perror("fork");
			return (1);
		}
		else if (id == 0)
		{
			set_signal_handler(DEFAULT);
			exit(ft_builts(scope, list_env));
		}
	}
	else
		ft_exit_status(ft_builts(scope, list_env));
	return (0);
}

void	ft_commands(t_shell *scope, t_node_env __attribute__ ((unused)) *tmp)
{
	close (scope->fd[1]);
	close (scope->s[0]);
	if (scope->infile != -1)
		dup2(scope->infile, 0);
	else if (scope->count != 0)
		dup2(scope->fd[0], 0);
	if (scope->outfile != -1)
		dup2(scope->outfile, 1);
	else if (scope->count != scope->stop)
		dup2(scope->s[1], 1);
	if (execve(scope->cmd[0], scope->cmd, scope->envp) == -1)
		ft_execv_error(scope->cmd[0]);
}

int	ft_pipe(t_node_env *list_env, t_shell *scope)
{
	int	id;

	(1) && (id = -1, scope->s[0] = -1, scope->s[1] = -1);
	scope->envp = ft_get_env(list_env);
	if (pipe(scope->s) == -1)
		return (1);
	if (ft_bool(scope->cmd) == 1)
	{
		set_signal_handler(DEFAULT);
		if (ft_exe_builts(scope, list_env) == 1)
			return (1);
	}
	else
	{
		(ft_exe_cmds(scope), id = fork());
		if (id == -1)
			return (perror("fork"), 1);
		else if (id == 0)
			(set_signal_handler(DEFAULT), ft_commands(scope, list_env));
	}
	dup2(scope->s[0], scope->fd[0]);
	(close (scope->outfile), close(scope->infile));
	(1) && (scope->infile = -1, scope->outfile = -1);
	(close (scope->s[0]), close (scope->s[1]));
	return (0);
}
