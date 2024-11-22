/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osslakri <osslakri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:28:30 by eenassir          #+#    #+#             */
/*   Updated: 2024/11/21 00:37:55 by osslakri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cheek_n(char *s)
{
	int	i;

	i = 1;
	while (s[i] && s[i] == 'n')
		i++;
	if (s[i] != '\0')
		return (1);
	return (0);
}

int	ft_echo(char **save)
{
	int		flag;
	int		i;

	i = 1;
	flag = 0;
	if (save[i] == NULL)
		write (1, "\n", 1);
	while (save[i] && (save[i][0] == '-' && save[i][1] == 'n'))
	{
		if (ft_cheek_n(save[i]))
			break ;
		flag = 1;
		i++;
	}
	while (save[i])
	{
		write (1, save[i], ft_strlen(save[i]));
		if (save[i + 1] != NULL)
			write (1, " ", 1);
		else if (save[i + 1] == NULL && flag != 1)
			write (1, "\n", 1);
		i++;
	}
	return (0);
}
