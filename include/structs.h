/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osslakri <osslakri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:53:38 by osslakri          #+#    #+#             */
/*   Updated: 2024/11/21 04:33:55 by osslakri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

enum
{
	TOKEN_CMD,//0
	TOKEN_REDIR_IN,//1
	TOKEN_REDIR_OUT,//2
	TOKEN_REDIR_APPEND,//3
	TOKEN_HEREDOC,//4
	TOKEN_PIPE,//5
	TOKEN_SPACE,//6
	TOKEN_Double_Q,//7
	TOKEN_Single_Q,//8
	TOKEN_DELIMITER,//9
	TOKEN_FILE
};

enum
{
	IGNORE,
	DEFAULT,
	HERDOC
};

typedef struct s_node_env
{
	struct s_node_env	*next;
	char				*key;
	char				*val;
	int					flag_val;
}	t_node_env;

typedef struct s_node_args
{
	char				*value;
	struct s_node_args	*prev;
	struct s_node_args	*next;
}	t_node_args;

typedef struct s_list_args
{
	t_node_args	*top;
	t_node_args	*bottom;
	int			size;
}	t_list_args;

typedef struct s_node
{
	char			*value;
	int				joinable;
	int				type;
	struct s_node	*prev;
	struct s_node	*next;
	int				flag_expend;
	t_list_args		*list_args;
	char			**scope;
	char			**scope_last;
}	t_node;

typedef struct s_list
{
	t_node			*top;
	t_node			*bottom;
	int				size;
	int				count_pipe;
	t_node_env		*env;
}	t_list;

typedef struct s_shell
{
	int		fd[2];
	int		s[2];
	int		count;
	int		stop;
	int		outfile;
	int		infile;
	int		flag_sta;
	char	**cmd;
	char	**re;
	char	**envp;
}	t_shell;

#endif
