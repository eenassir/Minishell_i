/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utile1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osslakri <osslakri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 14:53:38 by osslakri          #+#    #+#             */
/*   Updated: 2024/11/21 00:41:27 by osslakri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int sig)
{
	(void)sig;
	if (waitpid(-1, &sig, WNOHANG) == 0)
		return ;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	ft_exit_status(1);
}

void	handler(int signal)
{
	if (signal == SIGINT)
	{
		close(STDIN_FILENO);
		g_x = 0;
		ft_exit_status(1);
	}
}

void	set_signal_handler(int action)
{
	if (action == IGNORE)
	{
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (action == DEFAULT)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (action == HERDOC)
	{
		signal(SIGINT, handler);
		signal(SIGQUIT, SIG_IGN);
	}
}
