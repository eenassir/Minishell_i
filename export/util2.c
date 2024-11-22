/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osslakri <osslakri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 19:08:07 by eenassir          #+#    #+#             */
/*   Updated: 2024/11/21 00:39:40 by osslakri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_str_skip_char(char *s, int __attribute__ ((unused)) c)
{
	int		i;
	int		j;
	int		flag;
	char	*buffer;

	1 && (i = 0, j = 0, flag = 0);
	buffer = (char *)malloc(ft_strlen(s));
	if (!buffer)
		return (NULL);
	while (s[i] && s[i] != '+')
		buffer[j++] = s[i++];
	if (s[i] != '\0')
	{
		i++;
		while (s[i])
			buffer[j++] = s[i++];
	}
	buffer[j] = '\0';
	return (buffer);
}

t_node_env	*lst_new(void)
{
	t_node_env	*new;

	new = (t_node_env *)malloc(sizeof(t_node_env));
	if (!new)
		return (NULL);
	new->flag_val = 0;
	new->key = NULL;
	new->val = NULL;
	new->next = NULL;
	return (new);
}

void	ft_show_args(t_node_env *list)
{
	char	*s;

	while (list)
	{
		s = list->key;
		if (list->flag_val == 1 && list->key != NULL && list->val != NULL)
			printf ("declare -x %s=\"%s\"\n", list->key, list->val);
		else if (list->flag_val == 0 && list->key != NULL)
			printf ("declare -x %s\n", list->key);
		list = list->next;
	}
}
