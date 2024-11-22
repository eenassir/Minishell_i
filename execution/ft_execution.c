/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eenassir <eenassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:36:48 by eenassir          #+#    #+#             */
/*   Updated: 2024/11/21 11:51:38 by eenassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_put_args(t_node **list, char **save, char **re)
{
	int	i;
	int	j;

	(1) && (i = 0, j = 0);
	while ((*list) && (*list)->type != TOKEN_PIPE)
	{
		if (((*list) && (*list)->type == TOKEN_CMD) \
		|| (*list)->type == TOKEN_Double_Q \
		|| (*list)->type == TOKEN_Single_Q)
		{
			if ((*list)->value[0] != '\0')
				save[i++] = ft_gstrdup((*list)->value);
			else
			{
				if ((*list)->type == TOKEN_Double_Q \
				|| (*list)->type == TOKEN_Single_Q)
					save[i++] = ft_gstrdup("\0");
			}
		}
		if ((*list) && (*list)->type != TOKEN_CMD)
			re[j++] = ft_gstrdup((*list)->value);
		(*list) = (*list)->next;
	}
}

void	ft_herdoc_geter(t_shell *scope, t_node_env *list)
{
	int	i;
	int	fd[2];

	i = 0;
	fd[0] = -1;
	fd[1] = -1;
	while (scope->re[i])
	{
		if (ft_herdoc_status(-1) == 1)
			break ;
		if (scope->re[i][0] == '<' && scope->re[i][1] == '<' \
		&& ft_strlen(scope->re[i]) == 2)
		{
			close (scope->infile);
			if (pipe(fd) == -1)
			{
				fd_print(2, "pipe failed\n", NULL, NULL);
				scope->infile = -1;
			}
			herdoc(scope->re[i + 1], fd[1], list);
			scope->infile = fd[0];
		}
		i++;
	}
}

int	init_l(t_shell *scope, t_node *list)
{
	scope->count = 0;
	scope->infile = -1;
	scope->outfile = -1;
	scope->stop = ft_count_pipes(list);
	if (pipe(scope->fd) == -1)
		return (fd_print(2, "pipe failed!!\n", NULL, NULL), 1);
	return (0);
}

int	ft_execution(t_node *list, t_node_env *list_env)
{
	t_shell	scope;
	int		flag;

	flag = 0;
	if (init_l(&scope, list) == 1)
		return (1);
	while (list)
	{
		ft_get_cmdss(&scope, &list, list_env);
		if (ft_fd_geter(&scope) == 1)
		{
			scope.flag_sta = 1;
			continue ;
		}
		if (ft_herdoc_status(-1) == 1)
			break ;
		if (scope.cmd != NULL && scope.cmd[0] != NULL)
		{
			if (ft_pipe(list_env, &scope) == 1)
				return (ft_clear(&scope), 1);
		}
		if (list && list->type == TOKEN_PIPE)
			(1) && (list = list->next, scope.count++);
	}
	return (ft_clear(&scope), 0);
}
