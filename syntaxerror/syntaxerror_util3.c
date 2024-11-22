/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxerror_util3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eenassir <eenassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 03:20:26 by osslakri          #+#    #+#             */
/*   Updated: 2024/11/21 17:51:25 by eenassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pipe_syntax(t_node *tmp, int *in[], \
t_list *list, char **str)
{
	if (!tmp->next || !tmp->prev || (tmp->next \
	&& tmp->next->type == TOKEN_PIPE))
	{
		write(2, "minishell: syntax error near unexpected token `", 47);
		write(2, tmp->value, ft_strlen(tmp->value));
		write(2, "'\n", 2);
		ft_exit_status(258);
		*in[0] = 1;
		return (1);
	}
	tmp->scope = ft_split(str[*in[1]], ' ');
	(*in[1])++;
	list->count_pipe++;
	return (0);
}

int	set_last_scope(t_list *list, char **str, int i)
{
	t_node	*tmp;
	int		j;

	j = 0;
	tmp = list->top;
	while (tmp)
	{
		if (j == list->count_pipe - 1)
			tmp->scope_last = ft_split(str[i], ' ');
		if (tmp->type == TOKEN_PIPE)
			j++;
		tmp = tmp->next;
	}
	return (1);
}

int	checksyntaxe(int *checker, t_list *list, char **str)
{
	t_node	*tmp;
	int		i;
	int		*in[2];

	in[0] = checker;
	in[1] = &i;
	initialize_syntax_check(&tmp, &i, list);
	while (tmp)
	{
		if (check_heredoc_syntax(tmp, checker) || \
			(ft_isredirect(tmp->type) && \
			check_redirect_syntax(tmp, checker)) || \
			(tmp->type == TOKEN_PIPE && \
			check_pipe_syntax(tmp, in, list, str)))
			return (1);
		tmp = tmp->next;
	}
	return (set_last_scope(list, str, i));
}
