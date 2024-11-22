/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eenassir <eenassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 05:14:13 by osslakri          #+#    #+#             */
/*   Updated: 2024/11/21 15:51:15 by eenassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	count_length(int n)
{
	size_t	len;
	long	nb;

	nb = n;
	len = 0;
	if (nb < 0)
	{
		len++;
		nb = -nb;
	}
	if (nb == 0)
		len++;
	while (nb > 0)
	{
		len++;
		nb /= 10;
	}
	return (len);
}

static size_t	ft_tenpow(size_t n)
{
	size_t	ten;

	ten = 1;
	if (n == 0)
		return (ten);
	while (n > 0)
	{
		ten *= 10;
		n--;
	}
	return (ten);
}

char	*ft_itoa(int n)
{
	size_t	len;
	size_t	i;
	long	nb;
	char	*res;

	len = count_length(n);
	res = (char *)re_malloc(len + 1, NDS);
	nb = n;
	i = 0;
	if (!res)
		return (NULL);
	if (nb < 0)
	{
		*res = '-';
		nb = -nb;
		i++;
		len--;
	}
	while (len-- > 0)
	{
		*(res + i++) = ((nb / ft_tenpow(len)) % 10) + 48;
	}
	*(res + i) = '\0';
	return (res);
}
