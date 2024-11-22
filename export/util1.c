/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osslakri <osslakri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 19:05:37 by eenassir          #+#    #+#             */
/*   Updated: 2024/11/21 00:39:37 by osslakri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_exist(char *save, t_node_env *list)
{
	char		*val;
	char		*key;
	int			egale;

	key = NULL;
	val = NULL;
	egale = 0;
	if (ft_strchr(save, '=') != NULL)
		(div_string_by_egal(save, &key, &val), egale = 1);
	else
		key = ft_strdup(save);
	if (ft_parse_env_arg("export: `", key, save) == 1)
	{
		if (val != NULL)
			free (val);
		return (free (key), 1);
	}
	if (ft_put_arg1(list, key, val) == 0)
		ft_put_arg2(list, key, val, egale);
	return (0);
}

int	ft_put_arg3(char *key, char *val, t_node_env *list, char *save)
{
	if (ft_parse_env_arg("export: `", key, save) == 1)
	{
		free (key);
		if (val != NULL)
			free (val);
		return (1);
	}
	while (list && ft_strncmp(list->key, key, ft_strlen(list->key)) != 0)
		list = list->next;
	if (list && ft_strncmp(list->key, key, ft_strlen(list->key)) == 0)
	{
		if (val != NULL)
		{
			list->flag_val = 1;
			list->val = ft_gstrjoin(list->val, val);
		}
		return (1);
	}
	return (0);
}

void	cheeck_plus(char *save, t_node_env *list)
{
	char	*str;
	char	*key;
	char	*val;

	key = NULL;
	val = NULL;
	str = ft_str_skip_char(save, '+');
	div_string_by_egal(str, &key, &val);
	if (ft_put_arg3(key, val, list, save) != 1)
	{
		check_exist(str, list);
		if (val != NULL)
			free (val);
	}
}

int	ft_add_to_env(char *save, t_node_env *list)
{
	int	i;

	i = 0;
	while (save[i] && save[i] != '+')
		i++;
	if (save[i] == '+' && save[i + 1] != '=')
	{
		fd_print(2, "export: `", save, "': not a valid identifier\n");
		return (1);
	}
	if (save[i] == '+' && save[i + 1] == '=')
		cheeck_plus(save, list);
	else if (check_exist(save, list) == 1)
		return (1);
	return (0);
}
