/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osslakri <osslakri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 03:38:26 by osslakri          #+#    #+#             */
/*   Updated: 2024/11/21 03:48:42 by osslakri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_herdoc_status(int n)
{
	static int	var;

	if (n != -1)
		var = n;
	return (var);
}

int	ft_exit_status(int n)
{
	static int	var;

	if (n != -1)
		var = n;
	return (var);
}

void	handle_quotes(t_node **tmp, int quote_type)
{
	(*tmp)->type = quote_type;
	(*tmp)->value = ft_gstrjoin((*tmp)->value, (*tmp)->next->value);
	(*tmp)->next = (*tmp)->next->next;
}

void	handle_join(t_node **tmp)
{
	if ((*tmp)->next)
	{
		(*tmp)->value = ft_gstrjoin((*tmp)->value, (*tmp)->next->value);
		(*tmp)->next = (*tmp)->next->next;
	}
	else
		*tmp = (*tmp)->next;
}

void	join_tokens(t_node *token)
{
	t_node	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->joinable == 1)
		{
			if (tmp->next && tmp->next->type == TOKEN_Single_Q)
				handle_quotes(&tmp, TOKEN_Single_Q);
			else if (tmp->next && tmp->next->type == TOKEN_Double_Q)
				handle_quotes(&tmp, TOKEN_Double_Q);
			else
				handle_join(&tmp);
		}
		else
			tmp = tmp->next;
	}
}
