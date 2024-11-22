/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creation_util2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osslakri <osslakri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:53:38 by osslakri          #+#    #+#             */
/*   Updated: 2024/11/21 00:39:09 by osslakri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node_args	*c_node_args(char *value, t_node_args *prev)
{
	t_node_args	*node;

	node = malloc(sizeof(t_node_args));
	node->prev = prev;
	node->next = 0;
	node->value = value;
	return (node);
}

t_list_args	*c_list_args(void)
{
	t_list_args	*list;

	list = malloc(sizeof(t_list_args));
	list->bottom = 0;
	list->top = 0;
	list->size = 0;
	return (list);
}
