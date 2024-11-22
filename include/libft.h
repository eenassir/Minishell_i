/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eenassir <eenassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:20:57 by eenassir          #+#    #+#             */
/*   Updated: 2024/11/21 15:42:23 by eenassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "minishell.h"

typedef enum e_malloc
{
	NDS,
	ENVR,
	CLR_NDS,
	CLR_ENVR,
}	t_malloc;

typedef struct s_collector
{
	void				*ptr;
	struct s_collector	*next;
}	t_collector;

void	fd_print(int fd, char *str1, char *ptr, char *str2);
int		ft_strncmp(char *s1, char *s2, int n);
int		ft_count_word(char *s, char c);
char	**ft_split(char *s, char c);
int		ft_count_word(char *s, char c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(char *s, char c);
char	*ft_strdup(char *s);
bool	ft_strcmp(char *str, char *stri);
char	*getvalue(char *str, int len);
int		ft_atoi(char *save);
void	*re_malloc(size_t size, t_malloc flag);
char	*ft_gstrdup(char *s);
char	*ft_gstrjoin(char *s1, char *s2);

#endif