/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osslakri <osslakri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:30:40 by osslakri          #+#    #+#             */
/*   Updated: 2024/11/20 23:18:17 by osslakri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_text_expand(t_list *list, t_node *tok, char **tokens)
{
	int			i;
	char		*val;

	(1) && (i = 0, val = ft_gstrdup(""));
	while ((*tokens)[i])
	{
		if ((*tokens)[i] == '$')
		{
			if (!(*tokens)[i + 1] && (!tok->next || (tok->next
					&& tok->next->type != TOKEN_Double_Q && \
					tok->next->type != TOKEN_CMD
					&& tok->next->type != TOKEN_Single_Q)))
				val = ft_gstrjoin(val, "$");
			else
				handle_text_expand2(list, tokens, &val, &i);
		}
		else
			handle_text_expand4(tokens, &val, &i);
		i++;
	}
	*tokens = ft_gstrdup(val);
}

bool	ft_shouldexpand(t_node *node)
{
	t_node	*tmp;

	tmp = node;
	if (node->type == TOKEN_DELIMITER)
	{
		tmp->type = TOKEN_CMD;
		return (0);
	}
	if (node->type == TOKEN_HEREDOC)
	{
		tmp = tmp->next;
		if (tmp && tmp->type == TOKEN_SPACE)
			tmp = tmp->next;
		if (tmp)
			tmp->type = TOKEN_DELIMITER;
		return (0);
	}
	return (1);
}

void	expanding(t_list *list, t_node **tokens)
{
	t_node	*tok;

	tok = *tokens;
	while (tok)
	{
		if (ft_shouldexpand(tok))
		{
			if (tok->type == TOKEN_CMD)
			{
				handle_text_expand(list, tok, &tok->value);
				split_expand(tok, list);
			}
			else if (tok->type == TOKEN_Double_Q)
				handle_text_expand(list, tok, &tok->value);
		}
		tok = tok->next;
	}
}
