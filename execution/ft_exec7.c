/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec7.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eenassir <eenassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 10:49:26 by eenassir          #+#    #+#             */
/*   Updated: 2024/11/21 11:08:34 by eenassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_pipes(t_node *new)
{
	int		cpt;
	t_node	*tmp;

	tmp = new;
	cpt = 0;
	while (tmp)
	{
		if (tmp->value[0] == '|')
			cpt++;
		tmp = tmp->next;
	}
	return (cpt);
}

int	ft_count_env(t_node_env *new_env)
{
	int	cpt;

	cpt = 0;
	while (new_env)
	{
		if (new_env->key != NULL)
			cpt++;
		new_env = new_env->next;
	}
	return (cpt);
}

int	ft_count_cmd(t_node *struc)
{
	int	i;

	i = 0;
	while (struc && struc->type != TOKEN_PIPE)
	{
		if (struc->type == TOKEN_CMD || struc->type == TOKEN_Double_Q \
		|| struc->type == TOKEN_Single_Q)
			i++;
		struc = struc->next;
	}
	return (i);
}

int	ft_count_re(t_node *new)
{
	int	i;

	i = 0;
	while (new && new->type != TOKEN_PIPE)
	{
		if (new->type != TOKEN_CMD)
			i++;
		new = new->next;
	}
	return (i);
}

int	count_pipe(t_node *new)
{
	int	i;

	i = 0;
	while (new)
	{
		if (new->type == TOKEN_PIPE)
			i++;
		new = new->next;
	}
	return (i);
}
