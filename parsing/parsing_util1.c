/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_util1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eenassir <eenassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:53:38 by osslakri          #+#    #+#             */
/*   Updated: 2024/11/21 15:45:59 by eenassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_isspace(char c)
{
	return (c == 32 || c == '\t');
}

bool	check_spaces(char *str)
{
	int	i;

	i = -1;
	while (str && str[++i])
		if (!ft_isspace(str[i]))
			return (0);
	return (1);
}

bool	checkoperator(char c)
{
	return (c == '|' || c == '>' || c == '<' || c == '\'' || c == '\"');
}

void	reserve_space(t_list *list, char *str, int *i)
{
	char	*value;

	value = re_malloc(2, NDS);
	(1) && (value[0] = ' ', value[1] = '\0' );
	add_back(list, c_node(value, TOKEN_SPACE, list->bottom, 0));
	while (str[*i] && (str[*i] == 32 || str[*i] == '\t'))
		(*i)++;
}

void	error(const char *str)
{
	printf("%s\n", str);
	exit(1);
}
