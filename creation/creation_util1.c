/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creation_util1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eenassir <eenassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 09:53:38 by osslakri          #+#    #+#             */
/*   Updated: 2024/11/21 15:47:56 by eenassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*c_node(char *value, int type, t_node *prev, int flag)
{
	t_node	*node;

	node = re_malloc(sizeof(t_node), NDS);
	node->prev = prev;
	node->next = 0;
	node->value = value;
	node->type = type;
	node->flag_expend = 0;
	node->list_args = 0;
	node->joinable = flag;
	return (node);
}

t_list	*c_list(void)
{
	t_list	*list;

	list = re_malloc(sizeof(t_list), NDS);
	list->bottom = 0;
	list->top = 0;
	list->size = 0;
	list->count_pipe = 0;
	return (list);
}
