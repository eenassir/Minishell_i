/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_back.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osslakri <osslakri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 10:53:38 by osslakri          #+#    #+#             */
/*   Updated: 2024/11/21 00:38:58 by osslakri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_back(t_list *list, t_node *node)
{
	t_node	*tmp;

	if (!list)
		return ;
	if (!list->top)
	{
		list->top = node;
		list->bottom = node;
		return ;
	}
	tmp = list->top;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
	list->bottom = node;
	list->size++;
	list->bottom->next = 0;
}

void	add_back_args(t_list_args *list, t_node_args *node)
{
	t_node_args	*tmp;

	if (!list)
		return ;
	if (!list->top)
	{
		list->top = node;
		list->bottom = node;
		return ;
	}
	tmp = list->top;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
	list->bottom = node;
	list->size++;
	list->bottom->next = 0;
}

// void	add_back_env(t_list_env *list, t_node_env *node)
// {
// 	t_node_env	*tmp;

// 	if (!list)
// 		return ;
// 	if (!list->top)
// 	{
// 		list->top = node;
// 		list->bottom = node;
// 		return ;
// 	}
// 	tmp = list->top;
// 	while (tmp->next)
// 		tmp = tmp->next;
// 	tmp->next = node;
// 	list->bottom = node;
// 	list->size++;
// 	list->bottom->next = 0;
// }
