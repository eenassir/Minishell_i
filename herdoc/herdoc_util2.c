/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_util2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osslakri <osslakri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:48:21 by osslakri          #+#    #+#             */
/*   Updated: 2024/11/21 00:39:50 by osslakri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*heredoc_expand3(t_node_env *list, char **tok, char **str, int *i)
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
	tmp = get_val(*str, list);
	(!tmp) && (tmp = ft_gstrdup(""));
	(*i) += j;
	return (tmp);
}

void	heredoc_expand2(t_node_env *list, char **tok, char **val, int *i)
{
	char	*str;

	if ((*tok)[(*i) + 1] == '?')
		(1) && (str = ft_itoa(ft_exit_status(-1)),
			*val = ft_gstrjoin((*val), str), (*i)++);
	else if ((*tok)[(*i) + 1] >= '0' && (*tok)[(*i) + 1] <= '9')
	{
		*i += 1;
		*val = ft_gstrjoin((*val), heredoc_expand5(tok, &str, i));
	}
	else if ((*tok)[(*i) + 1] && (!ft_isalnum((*tok)[(*i) + 1])
			&& (*tok)[(*i) + 1] != '_'))
		(1) && (*val = ft_gstrjoin((*val), "$"),
			*val = ft_gstrjoin((*val), heredoc_expand5(tok, &str, i)));
	else if (!(*tok)[(*i) + 1] || (!ft_isalnum((*tok)[(*i) + 1])
			&& (*tok)[(*i) + 1] != '_'))
		(*val) = ft_gstrjoin((*val), "");
	else
		*val = ft_gstrjoin((*val), heredoc_expand3(list, tok, &str, i));
}

void	heredoc_expand4(char **tok, char **val, int *i)
{
	int	j;

	j = 0;
	while ((*tok + *i)[j] && (*tok + *i)[j] != '$')
		j++;
	*val = ft_gstrjoin(*val, ft_substr((*tok) + *i, 0, j));
	*i += j - 1;
}

void	heredoc_expand(t_node_env *list, char **tokens)
{
	int			i;
	char		*val;

	(1) && (i = 0, val = ft_gstrdup(""));
	while ((*tokens)[i])
	{
		if ((*tokens)[i] == '$')
			heredoc_expand2(list, tokens, &val, &i);
		else
			heredoc_expand4(tokens, &val, &i);
		i++;
	}
	free(*tokens);
	*tokens = ft_gstrdup(val);
}

void	herdoc(char *save, int fd, t_node_env *tmp)
{
	int		lfd;
	char	*line;

	set_signal_handler(HERDOC);
	lfd = dup(0);
	if (lfd < 0)
		printf("dup fails: !!");
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strncmp(line, save, ft_strlen(save)) == 0)
		{
			(close(fd), free(line));
			break ;
		}
		if (ft_strchr(line, '$') != NULL)
			heredoc_expand(tmp, &line);
		write(fd, line, ft_strlen(line));
		(write(fd, "\n", 1), free(line), line = NULL);
	}
	if (dup2(lfd, STDIN_FILENO) < 0)
		printf("dup2 fails: !!");
	if (g_x == 0)
		ft_herdoc_status(1);
}
