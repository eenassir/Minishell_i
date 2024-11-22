/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_util5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eenassir <eenassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:53:38 by osslakri          #+#    #+#             */
/*   Updated: 2024/11/21 16:39:43 by eenassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node_env	*ft_list_new(void)
{
	t_node_env	*lst;

	lst = re_malloc(sizeof(t_node_env), ENVR);
	lst->key = NULL;
	lst->val = NULL;
	lst->next = NULL;
	return (lst);
}

void	ft_addback(t_node_env **top, t_node_env **last)
{
	if (!(*top) || !(*last))
		return ;
	(*top)->next = (*last);
}

void	div_string_by_egal(char *str, char **div1, char **div2)
{
	int	count_div1;
	int	count_div2;
	int	i;
	int	j;

	if (str == NULL)
		return ;
	(1) && (count_div1 = 0, count_div2 = 0);
	while (str[count_div1] && str[count_div1] != '=')
		count_div1++;
	(1) && (i = count_div1, i++);
	while (str[i])
		1 && (count_div2++, i++);
	i = -1;
	(*div1) = re_malloc(count_div1 + 2, ENVR);
	(*div2) = re_malloc(count_div2 + 1, ENVR);
	if (!(*div1) || !(*div2))
		return ;
	while (++i < (count_div1))
		(*div1)[i] = str[i];
	(*div1)[i] = '\0';
	(1) && (i++, j = 0);
	while (str[i] && j < (count_div2))
		(*div2)[j++] = str[i++];
	(*div2)[j] = '\0';
}

t_node_env	*create_node(char *env_var)
{
	t_node_env	*node;
	char		*key;
	char		*val;

	node = ft_list_new();
	key = NULL;
	val = NULL;
	div_string_by_egal(env_var, &key, &val);
	node->key = ft_strdup(key);
	node->val = ft_strdup(val);
	node->flag_val = 1;
	return (node);
}

t_node_env	*parsing_envx(char **env)
{
	t_node_env	*list;
	t_node_env	*tmp;
	int			i;

	list = create_node(env[0]);
	tmp = list;
	i = 1;
	while (env[i])
	{
		tmp->next = create_node(env[i]);
		tmp = tmp->next;
		i++;
	}
	return (list);
}
