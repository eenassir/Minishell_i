/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eenassir <eenassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 20:00:32 by eenassir          #+#    #+#             */
/*   Updated: 2024/11/21 15:49:41 by eenassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlenc(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

char	**ft_free(char **p, int j)
{
	while (j > 0)
	{
		free (p[j]);
		j--;
	}
	free (p[j]);
	free (p);
	return (NULL);
}

char	*ft_substr(char *s, int start, int len)
{
	int		i;
	int		l;
	char	*p;

	i = 0;
	l = ft_strlen(s);
	if (len > l - start)
		len = l - start;
	if (start > l)
		len = 0;
	p = (char *)re_malloc(len + 1, NDS);
	while (s[start] && i < len)
		p[i++] = s[start++];
	p[i] = '\0';
	return (p);
}

char	**ft_split(char *s, char c)
{
	int		i;
	int		j;
	int		cpt;
	char	**p;
	int		len;

	i = 0;
	j = 0;
	len = 0;
	cpt = ft_count_word(s, c);
	p = (char **)re_malloc((cpt + 1) * sizeof (char *), NDS);
	while (j < cpt)
	{
		while (s[i] == c)
			i++;
		p[j] = ft_substr(s, i, len = ft_strlenc(s + i, c));
		if (!p[j++])
			return (ft_free(p, j - 1));
		i += len;
	}
	p[j] = NULL;
	return (p);
}
