/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxerror_util1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osslakri <osslakri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:53:38 by osslakri          #+#    #+#             */
/*   Updated: 2024/11/21 03:19:31 by osslakri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_isredirect(int t)
{
	return (t == TOKEN_HEREDOC || t == TOKEN_REDIR_APPEND || \
	t == TOKEN_REDIR_IN || t == TOKEN_REDIR_OUT);
}

bool	ft_iscommand(int type)
{
	return (type == TOKEN_CMD || type == TOKEN_Double_Q || \
	type == TOKEN_Single_Q);
}

bool	ft_iscommandexpend(t_node *node)
{
	t_node	*tmp;

	tmp = node;
	if (node->type == TOKEN_DELIMITER)
	{
		tmp->type = TOKEN_CMD;
		return (0);
	}
	if (node->type == TOKEN_HEREDOC)
	{
		tmp = tmp->next;
		if (tmp && tmp->type == TOKEN_SPACE)
			tmp = tmp->next;
		if (tmp)
			tmp->type = TOKEN_DELIMITER;
	}
	if (node->type == TOKEN_CMD && node->value[0] == '$')
		return (1);
	else if (node->type == TOKEN_Double_Q && node->value[0] == '$')
		return (1);
	return (0);
}

int	countlength(char *str, int *len)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '$' && str[i] != ' ')
		i++;
	*len = i;
	return (i);
}

char	*getvalue(char *str, int len)
{
	int		i;
	int		j;
	char	*dest;

	(1) && (dest = malloc(len + 2), i = 1, j = 0);
	while (str[i] && str[i] != '$' && str[i] != ' ')
		(1) && (dest[j] = str[i], i++, j++);
	dest[j] = '=';
	return (dest[j + 1] = '\0', dest);
}
