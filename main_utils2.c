/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eenassir <eenassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 03:40:58 by osslakri          #+#    #+#             */
/*   Updated: 2024/11/21 09:00:21 by eenassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_state(int __attribute__ ((unused)) status, t_node_env *tmp)
{
	while (tmp != NULL)
	{
		printf ("%s\n", tmp->key);
		tmp = tmp->next;
	}
}

void	ft_dif_re(t_node *tmp)
{
	while (tmp)
	{
		if (tmp->type == TOKEN_HEREDOC && tmp->next)
			tmp->next->type = TOKEN_DELIMITER;
		if (tmp->type == TOKEN_REDIR_APPEND && tmp->next)
		{
			if (tmp->next->value[0] != '\0')
				tmp->next->type = TOKEN_FILE;
		}
		if (tmp->type == TOKEN_REDIR_IN && tmp->next)
		{
			if (tmp->next->value[0] != '\0')
				tmp->next->type = TOKEN_FILE;
		}
		if (tmp->type == TOKEN_REDIR_OUT && tmp->next)
		{
			if (tmp->next->value[0] != '\0')
				tmp->next->type = TOKEN_FILE;
		}
		tmp = tmp->next;
	}
}

void	free_fds(void)
{
	int	i;

	i = 3;
	while (i < 10200)
	{
		if (close(i) == -1)
			return ;
		i++;
	}
}

void	check_arguments(int argc, char **argv)
{
	if (argc > 1)
	{
		fd_print(2, NULL, argv[1], ": No such file or directory");
		exit(127);
	}
}

t_node_env	*initialize_env(char **env, struct termios *ter)
{
	t_node_env	*list_env;

	tcgetattr(STDIN_FILENO, ter);
	list_env = parsing_envx(env);
	return (list_env);
}
