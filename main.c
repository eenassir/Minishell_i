/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eenassir <eenassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:53:38 by osslakri          #+#    #+#             */
/*   Updated: 2024/11/21 16:35:19 by eenassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_user_input(void)
{
	char	*input;

	input = readline("minishell $> ");
	if (!input)
	{
		write(1, "exit\n", 5);
		exit(ft_exit_status(-1));
	}
	add_history(input);
	return (input);
}

void	process_input(char *input, t_node_env *list_env)
{
	t_list	*list;
	t_list	*newlist;
	char	**str;
	int		checker;

	checker = 0;
	str = ft_split(input, '|');
	list = c_list();
	if (!parse_input(input, list))
	{
		free(input);
		return ;
	}
	free(input);
	list->env = list_env;
	expanding(list, &list->top);
	newlist = copylist(list);
	checksyntaxe(&checker, newlist, str);
	ft_dif_re(newlist->top);
	if (checker != 0)
		return ;
	join_tokens(newlist->top);
	ft_execution(newlist->top, list_env);
	free_fds();
}

void	shell_loop(t_node_env *list_env, struct termios *ter)
{
	char	*input;
	int		interactive;

	interactive = isatty(STDIN_FILENO);
	while (interactive)
	{
		g_x = 1;
		rl_catch_signals = 0;
		set_signal_handler(IGNORE);
		input = get_user_input();
		process_input(input, list_env);
		if (g_x)
			tcsetattr(STDIN_FILENO, TCSANOW, ter);
		re_malloc(0, NDS);
	}
	re_malloc(0, ENVR);
}

int	main(int argc, char **argv, char **env)
{
	struct termios	ter;
	t_node_env		*list_env;

	check_arguments(argc, argv);
	list_env = initialize_env(env, &ter);
	ft_herdoc_status(0);
	ft_exit_status(0);
	shell_loop(list_env, &ter);
	return (0);
}
