/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_util3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eenassir <eenassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:53:38 by osslakri          #+#    #+#             */
/*   Updated: 2024/11/21 15:48:20 by eenassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reserve_node_exec(t_list *list, char *str, int *i)
{
	if (str[*i] == '\'')
	{
		reserve_q_sgl(list, str, i);
		if (*i == -1)
			return ;
	}
	else if (str[*i] == '"')
	{
		reserve_q_dbl(list, str, i);
		if (*i == -1)
			return ;
	}
	else if (str[*i] == '|')
		reserve_pipe(list, str, i);
	else if (str[*i] == '>')
		reserve_redirect_dr(list, str, i);
	else if (str[*i] == '<')
		reserve_redirect_gc(list, str, i);
}

bool	check_pause(char c)
{
	return (c == ' ' || checkoperator(c));
}

void	reserve_cmd(t_list *list, char *str, int *i)
{
	int		count;
	int		flag;
	char	*value;

	count = 0;
	flag = 0;
	while (str[*i + count] && !check_pause(str[*i + count]))
		count++;
	if (str[*i + count] == '\'' || str[*i + count] == '"')
		flag = 1;
	value = re_malloc(count + 1, NDS);
	count = 0;
	while (str[*i + count] && !check_pause(str[*i + count]))
	{
		value[count] = str[*i + count];
		count++;
	}
	value[count] = '\0';
	add_back(list, c_node(value, TOKEN_CMD, list->bottom, flag));
	*i += count;
}

bool	parse_input(char *str, t_list *list)
{
	int	i;

	if (check_spaces(str))
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
			reserve_space(list, str, &i);
		else if (checkoperator(str[i]))
			reserve_node_exec(list, str, &i);
		else if (str[i] != ' ' && !checkoperator(str[i]))
			reserve_cmd(list, str, &i);
		if (i < 0)
			return (0);
	}
	return (1);
}

char	*get_val(char *value, t_node_env *head)
{
	char	*val;

	val = ft_strjoin(value, "=");
	while (head)
	{
		if (ft_strcmp(value, head->key))
			return (ft_gstrdup(head->val));
		head = head->next;
	}
	return (ft_gstrdup(""));
}
