/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_util4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osslakri <osslakri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 23:53:34 by osslakri          #+#    #+#             */
/*   Updated: 2024/11/20 23:54:20 by osslakri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand(t_node *tmp, t_list *list)
{
	char	*new_str;
	char	**splitted;
	t_node	*node[3];
	int		i;

	1 && (i = 0, node[0] = tmp->next);
	if (tmp->value[0] == '\'' || tmp->type == TOKEN_HEREDOC)
		return ;
	new_str = get_val(tmp->value, list->env);
	splitted = ft_split(new_str, ' ');
	if (splitted == NULL || splitted[0] == NULL || \
		(new_str && (!new_str[0] || !ft_strtrim(new_str, " ")[0])))
	{
		tmp->value = ft_strtrim(new_str, " ");
		return ;
	}
	1 && (tmp->value = splitted[i], node[1] = tmp);
	while (splitted[++i])
	{
		node[2] = c_node(splitted[i], tmp->type, node[1], 0);
		node[2]->next = node[0];
		1 && (tmp->next = node[2], node[1] = tmp, tmp = node[2]);
	}
	tmp->next = node[0];
}

t_list	*copylist(t_list *list)
{
	t_node	*tmp;
	t_list	*new_list;
	t_node	*node;

	1 && (tmp = list->top, new_list = c_list());
	while (tmp)
	{
		if (tmp && tmp->value && ft_strlen(tmp->value) == 0 && \
			tmp->type != TOKEN_Double_Q && tmp->type != TOKEN_Single_Q)
		{
			tmp = tmp->next;
			continue ;
		}
		if (tmp->type != TOKEN_SPACE)
		{
			node = \
			c_node(tmp->value, tmp->type, new_list->bottom, tmp->joinable);
			add_back(new_list, node);
		}
		tmp = tmp->next;
	}
	tmp = list->top;
	while (tmp)
		tmp = tmp->next;
	return (new_list);
}
