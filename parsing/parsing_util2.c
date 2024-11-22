/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_util2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eenassir <eenassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:53:38 by osslakri          #+#    #+#             */
/*   Updated: 2024/11/21 15:47:32 by eenassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reserve_q_sgl(t_list *list, char *str, int *i)
{
	int		count;
	char	*value;
	int		flag;

	1 && (count = 0, flag = 0, (*i)++);
	while (str[*i + count] && str[*i + count] != '\'')
		count++;
	if (str[*i + count] != '\'')
	{
		write(2, "minishell: Syntaxe Error Single Quote ", 38);
		write(2, "'\n", 2);
		ft_exit_status(258);
		*i = -1;
		return ;
	}
	count ++;
	if (str[*i + count] != '|' && str[*i + count] != '>' && str[*i + count] \
		!= '<' && str[*i + count] != ' ' && str[*i + count] != '\0')
		flag = 1;
	1 && (value = re_malloc(count + 1, NDS), count = 0);
	while (str[*i + count] && str[*i + count] != '\'')
		1 && (value[count] = str[*i + count], count++);
	value[count] = '\0';
	add_back(list, c_node(value, TOKEN_Single_Q, list->bottom, flag));
	(*i) += count + 1;
}

void	reserve_q_dbl(t_list *list, char *str, int *i)
{
	int		count;
	int		flag;
	char	*value;

	1 && (count = 0, flag = 0, (*i)++);
	while (str[*i + count] && str[*i + count] != '\"')
		count++;
	if (str[*i + count] != '\"')
	{
		write(2, "minishell: Syntaxe Error Double Quote ", 38);
		write(2, "'\n", 2);
		ft_exit_status(258);
		*i = -1;
		return ;
	}
	count++;
	if (str[*i + count] != '|' && str[*i + count] != '>' && str[*i + count] \
		!= '<' && str[*i + count] != ' ' && str[*i + count] != '\0')
		flag = 1;
	1 && (value = re_malloc(count + 1, NDS), count = 0);
	while (str[*i + count] && str[*i + count] != '\"')
		1 && (value[count] = str[*i + count], count++);
	value[count] = '\0';
	add_back(list, c_node(value, TOKEN_Double_Q, list->bottom, flag));
	(*i) += count + 1;
}

void	reserve_pipe(t_list *list, char *str, int *i)
{
	char	*value;

	(void)str;
	value = re_malloc(2, NDS);
	value[0] = '|';
	value[1] = '\0';
	add_back(list, c_node(value, TOKEN_PIPE, list->bottom, 0));
	*i += 1;
}

void	reserve_redirect_dr(t_list *list, char *str, int *i)
{
	char	*value;

	if ((str[*i] && str[*i] == '>') && (str[*i + 1] && str[*i + 1] == '>'))
	{
		value = re_malloc(3, NDS);
		value[0] = '>';
		value[1] = '>';
		value[2] = '\0';
		add_back(list, c_node(value, TOKEN_REDIR_APPEND, list->bottom, 0));
		*i += 2;
	}
	else
	{
		value = re_malloc(2, NDS);
		value[0] = '>';
		value[1] = '\0';
		add_back(list, c_node(value, TOKEN_REDIR_OUT, list->bottom, 0));
		*i += 1;
	}
}

void	reserve_redirect_gc(t_list *list, char *str, int *i)
{
	char	*value;

	if ((str[*i] && str[*i] == '<') && (str[*i + 1] && str[*i + 1] == '<'))
	{
		value = re_malloc(3, NDS);
		value[0] = '<';
		value[1] = '<';
		value[2] = '\0';
		add_back(list, c_node(value, TOKEN_HEREDOC, list->bottom, 0));
		*i += 2;
	}
	else
	{
		value = re_malloc(2, NDS);
		value[0] = '<';
		value[1] = '\0';
		add_back(list, c_node(value, TOKEN_REDIR_IN, list->bottom, 0));
		*i += 1;
	}
}
