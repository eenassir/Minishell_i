/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osslakri <osslakri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 11:25:38 by eenassir          #+#    #+#             */
/*   Updated: 2024/11/21 00:38:02 by osslakri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_node_env *list_env)
{
	t_node_env	*tmp;

	tmp = list_env;
	if (tmp != NULL)
	{
		while (tmp)
		{
			if (tmp->flag_val == 1 && tmp->key && tmp->val)
				printf ("%s=%s\n", tmp->key, tmp->val);
			else if (tmp->flag_val == 1 && tmp->key && tmp->val == NULL)
				printf ("%s=\n", tmp->key);
			else if (tmp->flag_val == 1 && tmp->key && tmp->val == NULL)
				printf ("%s=\n", tmp->key);
			tmp = tmp->next;
		}
	}
	return (0);
}
