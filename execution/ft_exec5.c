/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eenassir <eenassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 10:21:19 by eenassir          #+#    #+#             */
/*   Updated: 2024/11/21 11:37:25 by eenassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_outfile(t_shell *scope, int i)
{
	close (scope->infile);
	scope->infile = open (scope->re[i + 1], O_RDWR);
	if (scope->infile == -1)
	{
		fd_print (2, scope->re[i + 1], ": No such file or directory\n", NULL);
		return (1);
	}
	return (0);
}

int	ft_intfile1(t_shell *scope, int i)
{
	close (scope->outfile);
	scope->outfile = open (scope->re[i + 1], O_RDWR | O_CREAT | O_APPEND, 0777);
	if (scope->outfile == -1)
	{
		fd_print(2, scope->re[i + 1], ": No such file or directory\n", NULL);
		return (1);
	}
	return (0);
}

int	ft_infile2(t_shell *scope, int i)
{
	close (scope->outfile);
	scope->outfile = open (scope->re[i + 1], O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (scope->outfile == -1)
	{
		fd_print(2, scope->re[i + 1], ": No such file or directory\n", NULL);
		return (1);
	}
	return (0);
}

int	ft_fd_geter(t_shell *scope)
{
	int	i;

	i = 0;
	while (scope->re[i])
	{
		if (scope->re[i][0] == '<' && ft_strlen(scope->re[i]) == 1)
		{
			if (ft_outfile(scope, i) == 1)
				return (1);
		}
		else if (scope->re[i][0] == '>' && scope->re[i][1] == '>' \
		&& ft_strlen(scope->re[i]) == 2)
		{
			if (ft_intfile1(scope, i) == 1)
				return (1);
		}
		else if (scope->re[i][0] == '>' && ft_strlen(scope->re[i]) == 1)
		{
			if (ft_infile2(scope, i) == 1)
				return (1);
		}
		i++;
	}
	return (0);
}
