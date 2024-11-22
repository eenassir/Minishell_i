/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_util1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osslakri <osslakri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:53:38 by osslakri          #+#    #+#             */
/*   Updated: 2024/11/21 00:39:45 by osslakri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_strcmp(char *str, char *stri)
{
	int	i;

	i = 0;
	if (!str || !stri)
		return (0);
	while (str[i] || stri[i])
	{
		if (str[i] != stri[i])
			return (0);
		i++;
	}
	return (1);
}

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_isalnum(int c)
{
	if (ft_isdigit(c) || ft_isalpha(c))
		return (1);
	return (0);
}

char	*heredoc_expand5(char **tok, char **str, int *i)
{
	int		j;

	j = 1;
	if ((*tok + (*i))[j] == '_' || ft_isalpha((*tok + (*i))[j]))
	{
		j++;
		while ((*tok + (*i))[j] == '_' || ft_isalnum((*tok + (*i))[j]))
			j++;
	}
	(1) && (j--, *str = ft_substr(((*tok + (*i)) + 1), 0, j));
	(*i) += j;
	return (*str);
}
