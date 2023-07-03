/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaudet <bmaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 21:56:40 by bmaudet           #+#    #+#             */
/*   Updated: 2021/11/19 19:14:28 by bmaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define ADD_VAR 1
# define CMD_FOUND 2
# define ERROR -1

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stddef.h>
# include <signal.h>
# include <stdbool.h>
# include <sys/errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_redirs
{
	char			*line;
	char			*symbol;
	char			**argv;
	char			*cmd;
	int				input;
	int				output;
	int				i;
	char			*word;
	char			*executable;
	char			*target;
	struct s_redirs	*next;
	struct s_redirs	*prev;
}					t_redirs;

typedef struct s_lines
{
	char			*line;
	int				input;
	int				output;
	int				pid;
	struct s_lines	*next;
	struct s_lines	*prev;
	t_redirs		*redirs;
}					t_lines;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*prev;
	struct s_env	*next;
}					t_env;

typedef struct s_cmd
{
	char			**cmd_lst;
	int				(*ba[8])(char **argv);
}					t_cmd;

typedef struct s_shell
{
	t_cmd			*cmd;
	t_env			*env;
	t_lines			*lst;
	pid_t			pid;
	char			*usr;
	bool			hd;
	bool			hd_c;
	bool			hd_q;
	bool			path;
	bool			ms;
	int				exit;
}					t_shell;

t_shell					*g_shell;

// MINISHELL CORE

int					launch(t_lines *lst_l, t_lines *lstl, t_redirs *r, int s);
void				load_cmd(t_cmd *cmd);
void				load_user(bool tf);
int					load_env(t_env	*env, char **envt, int i, char *pwd);
void				change_shlvl(t_env	*env, int value, char *str);
void				add_shlvl(t_env	*env, int value, char *str);
t_env				*ft_create_elem(char *data);
t_env				*put_to_the_end(t_env *list, char *data);
void				complete_env(t_env	*env, char *pwd, char *str);
void				signal_handling(void);

// BUILTIN

int					cd(char **argv);
int					ft_export(char **argv);
int					sort_env(int i, int j, char **new, char *tmp);
char				**copy_env_exp(t_env *old, char *str, int i);
int					echo(char **argv);
int					env(char **argv);
int					unset(char **argv);
int					check_variable(char *str, char *data);
int					pwd(char **argv);
void				change_old_pwd(char *oldpwd);
int					ft_exit(char **argv);

// PARSE

int					open_file(char *symbol, char *file);
int					pipe_first(char *line);
int					too_many_pipes(char *line, int i, int x, int y);
int					launch_exec(t_redirs *lines, t_lines *lstl, int i, int ret);
int					is_even_quotes(char *line, char c);
int					parse(char *line, t_lines **lstl, int i, int k);
int					fill_stucture(t_lines **lstl, char *line);
int					find_symbol(char *line);
int					heredoc(t_redirs *list);
char				*heredoc_case(t_redirs *elem, char *line, int i);
char				**ft_split_argv(char *line);
char				*dollar(char *line, t_env *env, int i, char symbol);
char				**quotes(char **argv);
char				**copy_env(t_env *src, char *str);
char				*trunk_line(char *line, int i, int j);
void				prepare_exec(t_redirs *lst_lines);
void				change_env_exec(char *str);
t_redirs			*create_elem(char *data);

// FREE & EXIT

void				free_array(char **tab, int i);
void				env_clear(t_env *env);
void				ft_clean_elem(t_env	**env);
void				clear_lst_lines(t_lines **lst);
void				ft_exit_error(int er, char *msg, bool tf);
void				clear_cmd_lst(void);

// UTILS

int					empty_line(char *str);
int					empty(char *str);
char				*make_prompt(char *str);
int					go_malloc(void **str, int taille);

// WTF

char				*get_pwd(void);
void				print_data(t_lines *lst_lines);
void				print_data_redir(t_redirs *lst_lines);

#endif
