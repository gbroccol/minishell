/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvivian <pvivian@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 18:59:46 by pvivian           #+#    #+#             */
/*   Updated: 2020/11/20 16:31:11 by pvivian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "./libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/param.h>
# include <sys/stat.h>
# include <math.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <dirent.h>
# include <signal.h>

/*
**  commands
*/
# define TYPE_NO 0
# define TYPE_CD 1
# define TYPE_PWD 2
# define TYPE_ECHO 3
# define TYPE_EXIT 4
# define TYPE_EXPORT 5
# define TYPE_ENV 6
# define TYPE_UNSET 7
# define TYPE_BIN 8

/*
**  vars
*/
# define WRONG_ENV_SMB "\\|/ $%&()-:;<>?@^{}[]`~#./,*!\'\""
# define SHARE_SMB " \t\r\a"

typedef struct	s_pars
{
	int			pos;
	int			red_pos;
	char		**red_files;
	int			er_redir;
	int			red_nmb;
	char		*status;
	int			env_line;
	int			env_pos;
	int			env_str_pos;
	char		*env_str;
	char		*tmp;
	char		*tmp2;
}				t_pars;

typedef struct	s_token
{
	int			type_func;
	char		*cmd;
	char		**args;
	char		**redirect;
	char		**fd_red;
	int			pipe;
	int			flag_n;
}				t_token;

typedef struct	s_all
{
	int			syntax;
	int			ret_ex;
	int			ret_pars;
	char		*gnl_line;
	char		*gnl_tmp;
	char		**env;
	char		**local;
	int			status;
	int			fds[2];
	int			temp_0;
	int			temp_1;
	int			pre_pipe;
	char		*home;
	t_token		*tok;
	t_pars		*ps;
}				t_all;

void			parse_and_exec(t_all *all);
void			init_parse(t_all *all);
/*
**  parsing
*/
int				arguments(t_all *all, char *line, t_pars *ps);
int				check_gnl_line(t_all *all, char *str);
int				check_err_share_smb(t_all *all, char *str, t_pars *ps);
int				check_err_red_smb(t_all *all, char *str, t_pars *ps);
int				check_redir_files(t_all *all, char *str, t_pars *ps);
t_all			*clear_all(char **envp);
char			**save_env(char **envp, int size);
int				command(t_token *tok);
int				env(char *line, t_pars *ps, t_all *all);
int				parsing(t_all *all, t_pars *ps);
int				quote_no(t_all *all, char *line, t_pars *ps, int red_ignor);
int				quote_one(char *line, t_pars *ps);
int				quote_two(t_all *all, char *line, t_pars *ps);
int				dollar_no(t_all *all, char *line, t_pars *ps);
int				dollar_two(t_all *all, char *line, t_pars *ps);
int				redirect(t_all *all, char *line, char ***red_ar, t_pars *ps);

/*
**  execute
*/
int				execute(t_all *all);
char			**save_env(char **envp, int size);
char			*search_env(char **env, char *to_find, t_all *all);
int				launch(t_all *all, int r_redir);
void			parent(t_all *all, t_token *tok, pid_t pid, int r_redir);
void			child(t_all *all, t_token *tok);
int				shell_exit(t_all *all);
int				shell_cd(t_token *tokens, char **env, t_all *all, int *ret);
int				shell_pwd(t_all *all, int *ret);
int				shell_echo(t_token *token);
int				shell_export(t_token *token, t_all *all, int *ret);
int				shell_env(char **env);
int				shell_unset(t_token *token, t_all *all, int *ret);
char			*search_env(char **env, char *to_find, t_all *all);
int				find_path(char **env, char **executable, t_all *all);
char			**new_str(t_all *all, char *str);
int				check_new_env(t_all *all, char *str);
int				check_env_key(char *str);
int				replace_env(char **array, char *str);
int				ft_strlen_env(char *str);
int				check_vars_and_export(t_token *tok, t_all *all, int *stat);
void			update_home(t_all *all, char *str);
int				print_error(char *exec, char *exec2, char *err, int ret);
void			ft_eof(void);
int				fd_redir(t_token *token, int **tmp);
void			clear_fd_redir(t_token *token, int **tmp);
int				check_all_redirs(t_token *tok, int **t, t_all *all, int *r_red);
void			close_fd(t_all *all);
void			exit_all(t_all *all);
void			exit_all_tok(t_token *tok);
void			exit_all_ps(t_pars *ps);

#endif
