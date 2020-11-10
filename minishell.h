/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvivian <pvivian@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 18:59:46 by pvivian           #+#    #+#             */
/*   Updated: 2020/11/11 00:00:18 by pvivian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "errors.h"
# include "parsing.h"
# include "./libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/param.h>
# include <math.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <dirent.h>
# include <signal.h>

# include <stdio.h>            // remove fprintf(), printf(), stderr, getchar(), perror()

/*
**  commands
*/
# define TYPE_ERROR -2 // error(MSG_CMD_NOT_FOUND);
# define TYPE_NO 0
# define TYPE_CD 1
# define TYPE_PWD 2
# define TYPE_ECHO 3
# define TYPE_EXIT 4
# define TYPE_EXPORT 5
# define TYPE_ENV 6
# define TYPE_UNSET 7
# define TYPE_BIN 8


# define TYPE_PIPE 9
# define TYPE_RD_DB_OUT 10
# define TYPE_RD_S_OUT 11
# define TYPE_RD_INPUT 12

# define VAR_PWD 1

typedef struct		s_env
{
	int				env_line;
	int				env_pos;
	int				str_pos;
	char			*str;
}					t_env;

typedef struct		s_pars
{
	int				pos; // for gnl_line
	int				tmp_pos; // rm
	int				index;  // rm
	int				quote_start; // rm
	int				quote_finish;  // rm
	int				space; // rm
	char			*status;
	struct s_env	*ps_env;
}					t_pars;

typedef struct		s_token  // каждый лист замолочен
{
	int				type_func;
	char			**args;
	char			**redirect;
	int				pipe;
	
	char			*tmp;

	char			*cmd; // rm
	char			*flags; // rm
	char			*arg; // rm
	char			*redir; // rm
	char			*file; // rm
	int				flag_n; // rm
	char			**bin_tok; // rm
}					t_token;

typedef struct		s_all
{
	int				wait_cmd;
	int				ret_ex;
	int				ret_pars;
	char			*gnl_line;
	char			*gnl_tmp;
	char			**env;
	int				status;
	int				fds[2];
	int				temp_0;
	int				temp_1;
	int				pre_pipe;
	t_token			*tok;
	t_pars			*ps; // структура для парсинга
}					t_all;

/*
**  parsing
*/

t_all				*clear_all();
void				clear_parsing(t_pars *ps, int clear_place);
int					parsing(t_all *all, t_pars *ps);
void				command(char *line, t_token *tok, t_pars *ps, char **env);

int					arguments(t_all *all, char *line, t_token *tok, t_pars *ps, char **env);

int					quote_no(char *line, t_token *tok, t_pars *ps, char **env, int redir_ignor);
int					quote_one(char *line, t_token *tok, t_pars *ps);
int					quote_two(char *line, t_token *tok, t_pars *ps, char **env);

int					cmd_quote_no(char *line, t_token *tok, t_pars *ps, char **env);
int					cmd_quote_one(char *line, t_token *tok, t_pars *ps);
int					cmd_quote_two(char *line, t_token *tok, t_pars *ps, char **env);

void				check_flags(char *line, t_pars *ps, t_token *tok, char **env);
int					is_env(char *line, t_pars *ps, char **env);
void				check_env(char *line, t_env *ps_env, char **env);
void				check_redirect(char *line, t_pars *ps, t_token *tok, char **env);
char				*check_shielding(char *line);
void				create_bin_tok(t_token *tok);

/*
**  execute
*/
int					execute(t_all *all);
void				kill_process(int signal);
char				**save_env(char **envp, int size);
char				*search_env(char **env, char *to_find);
void				ft_free_array(char **to_free);
int					launch(t_all *all);
int					lsh_exit(t_all *all);
int					lsh_cd(t_token *token, char **env);
int					lsh_pwd(void);
int					lsh_echo(t_token *token, t_all *all);

#endif
