/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eenassir <eenassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 09:19:57 by eenassir          #+#    #+#             */
/*   Updated: 2024/11/21 09:55:26 by eenassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_tab(int in, int out)
{
	if (in != 0 && in != 1)
		close(in);
	if (out != 0 && out != 1)
		close(out);
}

void	ft_clear(t_shell *scope)
{
	int	status;

	status = 0;
	ft_herdoc_status(0);
	close_tab(scope->s[0], scope->s[1]);
	(close (scope->infile), close (scope->outfile));
	(close (scope->fd[0]), close (scope->fd[1]));
	while (waitpid(-1, &status, 0) != -1 && errno != ECHILD)
	{
		if (WIFEXITED(status))
			ft_exit_status(WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGQUIT)
				printf("Quit: 3\n");
			else if (WTERMSIG(status) == SIGINT)
				write(1, "\n", 1);
			ft_exit_status((128 + WTERMSIG(status)));
		}
	}
	if (scope->flag_sta == 1)
		ft_exit_status(1);
}
