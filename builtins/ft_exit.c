/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eenassir <eenassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 15:15:00 by eenassir          #+#    #+#             */
/*   Updated: 2024/11/21 15:58:12 by eenassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cheeck(char *tmp)
{
	int	i;

	i = 0;
	if (!tmp)
		return (1);
	if (tmp[0] == '+' || tmp[0] == '-')
		i++;
	while (tmp[i])
	{
		if (!(tmp[i] >= '0' && tmp[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

void	ft_util1(char *save)
{
	fd_print(2, "exit: ", save, ": numiric argument required\n");
	ft_exit_status(1);
}

void	ft_util2(void)
{
	fd_print(2, "exit: too many arguments\n", NULL, NULL);
	ft_exit_status(1);
}

void	ft_exit(char **save)
{
	int	value;

	if (save[1] && save[2])
	{
		if (ft_cheeck(save[1]) == 1)
			ft_util1(save[1]);
		else if (ft_cheeck(save[1]) == 0)
			ft_util2();
	}
	else if (save[1] && ft_cheeck(save[1]) == 1)
	{
		fd_print(2, "exit: ", save[1], ": numiric argument required\n");
		ft_exit_status(255);
	}
	if (save[1] != NULL && save[2] == NULL && ft_cheeck(save[1]) != 1)
	{
		value = ft_atoi(save[1]);
		if (value == -1 || value > 0)
			exit(ft_exit_status((value % 256)));
		else if (value != -1 && value < 0)
			exit(ft_exit_status((value % 256) + 256));
	}
	if (save[1] == NULL)
		(ft_exit_status(0), exit(0));
}
