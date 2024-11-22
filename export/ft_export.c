/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osslakri <osslakri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 19:01:36 by eenassir          #+#    #+#             */
/*   Updated: 2024/11/21 00:39:31 by osslakri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parse_env_arg(char *name, char *save, char *str)
{
	int	i;

	i = 1;
	if (!(save[0] >= 'a' && save[0] <= 'z') \
	&& !(save[0] >= 'A' && save[0] <= 'Z') && save[0] != '_')
		return (fd_print(2, name, str, "': not a valid identifier\n"), 1);
	while (save[i] && save[i] != '=')
	{
		if (!(save[i] >= 'a' && save[i] <= 'z') && !(save[i] >= 'A' \
		&& save[i] <= 'Z') && !(save[i] >= '0' && save[i] <= '9') && \
		save[i] != '_' && save[i] != '+')
			return (fd_print(2, name, str, "': not a valid identifier\n"), 1);
		i++;
	}
	return (0);
}

int	ft_put_arg1(t_node_env *list, char *key, char *val)
{
	while (list && ft_strncmp(list->key, key, ft_strlen(list->key)) != 0)
		list = list->next;
	if (list != NULL && ft_strncmp(key, list->key, ft_strlen(key)) == 0)
	{
		if (val != NULL)
		{
			list->flag_val = 1;
			list->val = ft_gstrdup(val);
		}
		return (1);
	}
	return (0);
}

void	ft_put_arg2(t_node_env *list, char *key, char *val, int egale)
{
	t_node_env	*var;

	while (list->next != NULL)
		list = list->next;
	var = lst_new();
	var->key = ft_gstrdup(key);
	if (val != NULL)
	{
		var->flag_val = 1;
		var->val = ft_gstrdup(val);
	}
	else if (val == NULL && egale == 1)
		var->flag_val = 1;
	else
		var->flag_val = 0;
	list->next = var;
	if (val != NULL)
		free (val);
	(free (key));
}

int	ft_export(char **save, t_node_env *env_tmp)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	if (!save[1])
		return (ft_show_args(env_tmp), 0);
	while (save[i] != NULL)
	{
		if (ft_add_to_env(save[i], env_tmp))
			status = 1;
		i++;
	}
	return (status);
}
