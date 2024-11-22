/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eenassir <eenassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:53:38 by osslakri          #+#    #+#             */
/*   Updated: 2024/11/21 13:47:30 by eenassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./structs.h"
# include <stdio.h>
# include <termios.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <fcntl.h>
# include <unistd.h>
# include <limits.h>
# include <sys/errno.h>
# include <signal.h>
# include "libft.h"
# include <sys/stat.h>

int			g_x;
void		add_back_args(t_list_args *list, t_node_args *node);
t_node_args	*c_node_args(char *value, t_node_args *prev);
t_list_args	*c_list_args(void);
void		handler(int signal);
void		handler_signel(int signal, siginfo_t *siginfo, void *vd);
void		add_back(t_list *list, t_node *node);
t_node		*c_node(char *value, int type, t_node *prev, int flag);
t_list		*c_list(void);
void		reserve_space(t_list *list, char *str, int *i);
void		reserve_q_sgl(t_list *list, char *str, int *i);
void		reserve_q_dbl(t_list *list, char *str, int *i);
void		reserve_pipe(t_list *list, char *str, int *i);
void		reserve_redirect_dr(t_list *list, char *str, int *i);
void		reserve_redirect_gc(t_list *list, char *str, int *i);
void		reserve_node_exec(t_list *list, char *str, int *i);
bool		check_pause(char c);
void		reserve_cmd(t_list *list, char *str, int *i);
bool		parse_input(char *str, t_list *list);
bool		checkoperator(char c);
bool		ft_isspace(char c);
bool		check_spaces(char *str);
t_list		*copylist(t_list *list);
int			checksyntaxe(int *checker, t_list *list, char **str);
bool		ft_strcmp(char *str, char *stri);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
char		*heredoc_expand5(char **tok, char **str, int *i);
char		*heredoc_expand3(t_node_env *list, char **tok, char **str, int *i);
void		heredoc_expand2(t_node_env *list, char **tok, char **val, int *i);
void		heredoc_expand4(char **tok, char **val, int *i);
void		herdoc(char *save, int fd, t_node_env *tmp);
int			ft_herdoc_status(int n);
int			ft_exit_status(int n);
int			ft_strlen(char *str);
bool		ft_iscommandexpend(t_node *node);
void		add_list_args(t_node *tmp);
t_node_env	*parsing_envx(char **env);
void		div_string_by_egal(char *str, char **div1, char **div2);
char		*handle_text_expand5(char **tok, char **str, int *i);
void		split_expand(t_node *tmp, t_list *list);
char		*handle_text_expand3(t_list *list, char **tok, char **str, int *i);
void		handle_text_expand2(t_list *list, char **tok, char **val, int *i);
void		handle_text_expand4(char **tok, char **val, int *i);
int			countlength(char *str, int *len);
bool		ft_iscommand(int type);
void		initialize_syntax_check(t_node **tmp, int *i, t_list *list);
int			check_heredoc_syntax(t_node *tmp, int *checker);
bool		ft_isredirect(int t);
int			check_redirect_syntax(t_node *tmp, int *checker);
int			ft_herdoc_status(int n);
int			ft_exit_status(int n);
void		handle_quotes(t_node **tmp, int quote_type);
void		handle_join(t_node **tmp);
void		join_tokens(t_node *token);
void		ft_state(int __attribute__ ((unused)) status, t_node_env *tmp);
void		ft_dif_re(t_node *tmp);
void		free_fds(void);
void		check_arguments(int argc, char **argv);
t_node_env	*initialize_env(char **env, struct termios *ter);

//--------------------------------------------------execution:
int			ft_export(char **save, t_node_env *env_tmp);
void		ft_show_args(t_node_env *list);
int			ft_add_to_env(char *save, t_node_env *list);
char		*ft_str_skip_char(char *s, int c);
int			ft_put_arg1(t_node_env *list, char *key, char *val);
void		ft_put_arg2(t_node_env *list, char *key, char *val, int egale);
int			ft_unset(char **save, t_node_env **var);
int			ft_parse_env_arg(char *name, char *save, char *str);
int			ft_env(t_node_env *list_env);
int			ft_cd(char **save, t_node_env *list_env);
int			ft_pwd(void);
int			ft_echo(char **save);
void		ft_exit(char **save);
char		*ft_strtrim(char *s1, char *set);
char		*ft_substr(char *s, int start, int len);
char		*ft_itoa(int n);
void		expanding(t_list *list, t_node **tokens);
char		*get_val(char *value, t_node_env *head);
void		set_signal_handler(int action);
t_node_env	*lst_new(void);
int			ft_execution(t_node *list, t_node_env *list_env);
void		ft_clear(t_shell *l);
int			ft_pipe(t_node_env *list_env, t_shell *scope);
int			ft_builts(t_shell *scope, t_node_env *list);
int			ft_fd_geter(t_shell *scope);
void		ft_execv_error(char *cmd);
int			ft_count_pipes(t_node *new);
int			ft_count_env(t_node_env *new_env);
int			ft_count_cmd(t_node *struc);
int			ft_count_re(t_node *new);
int			count_pipe(t_node *new);
int			ft_exe_cmds(t_shell *scope);
void		ft_get_cmdss(t_shell *scope, t_node **list, t_node_env *list_env);
void		ft_put_args(t_node **list, char **save, char **re);
void		ft_herdoc_geter(t_shell *scope, t_node_env *list);

#endif
