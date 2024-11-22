/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tax_collector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eenassir <eenassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:53:38 by osslakri          #+#    #+#             */
/*   Updated: 2024/11/21 15:44:48 by eenassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	frr_adds(t_collector **taxes)
{
	t_collector	*current;
	t_collector	*temp;

	if (!taxes || !*taxes)
		return ;
	current = *taxes;
	while (current)
	{
		temp = current;
		current = current->next;
		free(temp->ptr);
		free(temp);
	}
	*taxes = NULL;
}

static void	lst_grbg(t_collector **taxes, void *ptr)
{
	t_collector	*new_tax;

	new_tax = malloc(sizeof(t_collector));
	if (!new_tax)
		return (perror("Malloc :"));
	new_tax->ptr = ptr;
	new_tax->next = *taxes;
	*taxes = new_tax;
}

void	*re_malloc(size_t size, t_malloc flag)
{
	static t_collector	*freq_taxes;
	static t_collector	*end_taxes;
	void				*ptr;

	if (flag == NDS)
	{
		ptr = malloc(size);
		if (!ptr)
			return (perror("Malloc :"), NULL);
		lst_grbg(&freq_taxes, ptr);
		return (ptr);
	}
	else if (flag == ENVR)
	{
		ptr = malloc(size);
		if (!ptr)
			return (perror("Malloc :"), NULL);
		return (lst_grbg(&end_taxes, ptr), ptr);
	}
	else if (flag == CLR_NDS)
		frr_adds(&freq_taxes);
	else if (flag == CLR_ENVR)
		frr_adds(&end_taxes);
	return (NULL);
}
