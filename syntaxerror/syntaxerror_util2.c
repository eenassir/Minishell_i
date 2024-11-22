/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxerror_util2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osslakri <osslakri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 03:19:37 by osslakri          #+#    #+#             */
/*   Updated: 2024/11/21 05:14:14 by osslakri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_list_args(t_node *tmp)
{
	char	*str;
	int		i;
	int		len;

	1 && (str = tmp->value, i = 0);
	tmp->list_args = c_list_args();
	while (str[i])
	{
		len = 0;
		if (str[i] == '$')
		{
			(!tmp->flag_expend) && (tmp->flag_expend = 1);
			add_back_args(tmp->list_args, c_node_args(getvalue(&str[i], \
				countlength(&str[i], &len)), tmp->list_args->bottom));
			i += len;
		}
		if (!len)
			i++;
	}
}

void	redifine(t_node *tmp)
{
	while (tmp)
	{
		if (tmp->value[0] == '<' && tmp->value[1] == '<' && \
		ft_strlen(tmp->value) == 2)
			tmp->type = TOKEN_HEREDOC;
		if (tmp->value[0] == '<' && ft_strlen(tmp->value) == 1)
			tmp->type = TOKEN_REDIR_IN;
		if (tmp->value[0] == '>' && tmp->value[1] == '>' && \
		ft_strlen(tmp->value) == 2)
			tmp->type = TOKEN_REDIR_APPEND;
		if (tmp->value[0] == '>' && ft_strlen(tmp->value) == 1)
			tmp->type = TOKEN_REDIR_OUT;
		if (tmp->value[0] == '|' && ft_strlen(tmp->value) == 1)
			tmp->type = TOKEN_PIPE;
		tmp = tmp->next;
	}
}

void	initialize_syntax_check(t_node **tmp, int *i, t_list *list)
{
	*i = 0;
	*tmp = list->top;
	redifine(*tmp);
}

int	check_heredoc_syntax(t_node *tmp, int *checker)
{
	if (tmp->type == TOKEN_HEREDOC && tmp->next && \
		tmp->next->type != TOKEN_CMD && tmp->next->type != TOKEN_DELIMITER)
	{
		write(2, "minishell: syntax error near unexpected token `", 47);
		write(2, tmp->value, ft_strlen(tmp->value));
		write(2, "'\n", 2);
		ft_exit_status(258);
		*checker = 1;
		return (1);
	}
	return (0);
}

int	check_redirect_syntax(t_node *tmp, int *checker)
{
	if (!tmp->next || (tmp->next && !ft_iscommand(tmp->next->type)))
	{
		write(2, "minishell: syntax error near unexpected token `", 47);
		write(2, tmp->value, ft_strlen(tmp->value));
		write(2, "'\n", 2);
		ft_exit_status(258);
		*checker = 1;
		return (1);
	}
	return (0);
}
