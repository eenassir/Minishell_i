/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eenassir <eenassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 19:11:48 by eenassir          #+#    #+#             */
/*   Updated: 2024/11/21 13:47:56 by eenassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_wd(char *s, char *ptr, t_node_env *list)
{
	t_node_env	*tmp;

	tmp = list;
	while (tmp && ft_strncmp(tmp->key, ptr, ft_strlen(ptr)) != 0)
		tmp = tmp->next;
	if (tmp && ft_strncmp(tmp->key, ptr, ft_strlen(ptr)) == 0)
		tmp->val = ft_gstrdup(s);
	else
		return ;
}

char	*ft_static(char *s)
{
	static char	*d;

	if (s != NULL)
	{
		d = NULL;
		d = ft_gstrdup(s);
	}
	else
		return (d);
	return (NULL);
}

int	ft_home(t_node_env *tmp_env)
{
	char	*s;

	while (tmp_env && ft_strncmp(tmp_env->key, "HOME", 4) != 0)
		tmp_env = tmp_env->next;
	if (tmp_env != NULL && ft_strncmp(tmp_env->key, "HOME", 4) == 0)
	{
		s = getcwd(NULL, 0);
		((void)ft_static(s), free (s));
		ft_wd(ft_static(NULL), "OLDPWD=", tmp_env);
		if (chdir(tmp_env->val) == -1)
		{
			fd_print(2, "cd: ", tmp_env->val, " No such file or directory\n");
			return (1);
		}
		s = getcwd(NULL, 0);
		(ft_wd(s, "PWD", tmp_env), free (s));
	}
	else
	{
		printf ("minishell: cd: HOME not set\n");
		return (1);
	}
	return (0);
}

int	ft_util(char *an, t_node_env *list_env)
{
	an = getcwd(NULL, 0);
	(ft_wd(an, "OLDPWD", list_env), free(an));
	if (ft_static(NULL) != NULL)
		printf ("%s\n", ft_static(NULL));
	else
		return (fd_print(2, "minishell: cd: OLDPWD not set\n", 0, 0), 1);
	(chdir(ft_static(NULL)), (void)ft_static(an));
	an = getcwd(NULL, 0);
	(ft_wd(an, "PWD", list_env), free (an));
	return (0);
}

int	ft_cd(char **save, t_node_env *list_env)
{
	char	*an;

	an = NULL;
	if (save[1] == NULL)
	{
		if (ft_home(list_env) == 1)
			return (1);
	}
	else if (save[1][0] == '-' && save[1][1] == '\0')
	{
		if (ft_util(an, list_env) == 1)
			return (1);
	}
	else if (save[1] != NULL)
	{
		an = getcwd(NULL, 0);
		((void)ft_static(an), free(an));
		ft_wd(ft_static(NULL), "OLDPWD", list_env);
		if (chdir(save[1]) == -1)
			return (fd_print (2, "cd: ", save[1], \
			": No sush file or directory\n"), 1);
		an = getcwd(NULL, 0);
		(ft_wd(an, "PWD", list_env), free (an));
	}
	return (0);
}
