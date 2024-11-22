/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osslakri <osslakri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:53:38 by osslakri          #+#    #+#             */
/*   Updated: 2024/11/21 00:40:59 by osslakri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_text_expand5(char **tok, char **str, int *i)
{
	int		j;

	j = 1;
	if ((*tok + (*i))[j] == '_' || ft_isalpha((*tok + (*i))[j]))
	{
		j++;
		while ((*tok + (*i))[j] == '_' || ft_isalnum((*tok + (*i))[j]))
			j++;
	}
	(1) && (j--, *str = ft_substr(((*tok + (*i)) + 1), 0, j));
	(*i) += j;
	return (*str);
}

void	split_expand(t_node *tmp, t_list __attribute__ ((unused)) *list)
{
	char	**splitted;
	t_node	*node[3];
	int		i;

	1 && (i = 0, node[0] = tmp->next);
	if (tmp->value[0] == '\'' || tmp->type == TOKEN_HEREDOC)
		return ;
	splitted = ft_split(tmp->value, ' ');
	if (splitted == NULL || splitted[0] == NULL || (tmp->value && \
	(!tmp->value[0] || !ft_strtrim(tmp->value, " ")[0])))
	{
		tmp->value = ft_strtrim(tmp->value, " ");
		return ;
	}
	tmp->value = splitted[i];
	node[1] = tmp;
	while (splitted[++i])
	{
		node[2] = c_node(splitted[i], tmp->type, node[1], 0);
		node[2]->next = node[0];
		1 && (tmp->next = node[2], node[1] = tmp, tmp = node[2]);
	}
	tmp->next = node[0];
}

char	*handle_text_expand3(t_list *list, char **tok, char **str, int *i)
{
	int		j;
	char	*tmp;

	j = 1;
	if ((*tok + (*i))[j] == '_' || ft_isalpha((*tok + (*i))[j]))
	{
		j++;
		while ((*tok + (*i))[j] == '_' || ft_isalnum((*tok + (*i))[j]))
			j++;
	}
	(1) && (j--, *str = ft_substr(((*tok + (*i)) + 1), 0, j));
	tmp = get_val(*str, list->env);
	(!tmp) && (tmp = ft_gstrdup(""));
	(*i) += j;
	return (tmp);
}

void	handle_text_expand2(t_list *list, char **tok, char **val, int *i)
{
	char	*str;

	if ((*tok)[(*i) + 1] == '?')
		(1) && (str = ft_itoa(ft_exit_status(-1)),
			*val = ft_gstrjoin((*val), str), (*i)++);
	else if ((*tok)[(*i) + 1] >= '0' && (*tok)[(*i) + 1] <= '9')
	{
		*i += 1;
		*val = ft_gstrjoin((*val), handle_text_expand5(tok, &str, i));
	}
	else if ((*tok)[(*i) + 1] && (!ft_isalnum((*tok)[(*i) + 1])
			&& (*tok)[(*i) + 1] != '_'))
		(1) && (*val = ft_gstrjoin((*val), "$"),
			*val = ft_gstrjoin((*val), handle_text_expand5(tok, &str, i)));
	else if (!(*tok)[(*i) + 1] || (!ft_isalnum((*tok)[(*i) + 1])
			&& (*tok)[(*i) + 1] != '_'))
		(*val) = ft_gstrjoin((*val), "");
	else
		*val = ft_gstrjoin((*val), handle_text_expand3(list, tok, &str, i));
}

void	handle_text_expand4(char **tok, char **val, int *i)
{
	int	j;

	j = 0;
	while ((*tok + *i)[j] && (*tok + *i)[j] != '$')
		j++;
	*val = ft_gstrjoin(*val, ft_substr((*tok) + *i, 0, j));
	*i += j - 1;
}
