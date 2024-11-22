/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eenassir <eenassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 09:03:15 by eenassir          #+#    #+#             */
/*   Updated: 2024/11/21 09:03:35 by eenassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_atoi(char *save)
{
	int	i;
	int	signe;
	int	result;

	i = 0;
	signe = 1;
	result = 0;
	if (save[0] == '+' || save[0] == '-')
	{
		if (save[0] == '-')
			signe *= -1;
		i++;
	}
	while ((save[i] >= '0' && save[i] <= '9'))
	{
		result = result * 10 + save[i] - 48;
		if ((result < 0 && signe == 1) || (result * -1 > 0 && signe == -1))
			return (-1);
		i++;
	}
	return (result * signe);
}
