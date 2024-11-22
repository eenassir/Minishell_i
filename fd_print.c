/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eenassir <eenassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 08:57:25 by eenassir          #+#    #+#             */
/*   Updated: 2024/11/21 08:57:27 by eenassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fd_print(int fd, char *str1, char *ptr, char *str2)
{
	write (fd, "minishell: ", ft_strlen("minishell :"));
	if (str1 != NULL)
		write(fd, str1, ft_strlen(str1));
	if (ptr != NULL)
		write (fd, ptr, ft_strlen(ptr));
	if (str2 != NULL)
		write (fd, str2, ft_strlen(str2));
}
