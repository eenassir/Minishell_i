/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osslakri <osslakri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 18:58:39 by eenassir          #+#    #+#             */
/*   Updated: 2024/11/21 00:38:20 by osslakri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_core(char *s, t_node_env **var)
{
	t_node_env	*tmp;

	if (!s || !var || !*var)
		return ;
	if (s[0] == '_' && ft_strlen(s) == 1)
		return ;
	tmp = *var;
	while (tmp)
	{
		if (tmp->key && s)
		{
			if (ft_strncmp(tmp->key, s, ft_strlen(s)) == 0)
			{
				free(tmp->key);
				free(tmp->val);
				tmp->key = NULL;
				tmp->val = NULL;
				break ;
			}
		}
		tmp = tmp->next;
	}
}

int	ft_unset(char **save, t_node_env **var)
{
	int	i;
	int	status;

	status = 0;
	if (!save || !var || !(*var))
		return (0);
	i = 1;
	while (save[i])
	{
		if (ft_parse_env_arg("unset: `", save[i], save[i]) == 0)
			ft_core(save[i], var);
		else
			status = 1;
		i++;
	}
	return (status);
}
