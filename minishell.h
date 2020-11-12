/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvivian <pvivian@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 18:59:46 by pvivian           #+#    #+#             */
/*   Updated: 2020/11/11 17:31:50 by pvivian          ###   ########.fr       */
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

# define WRONG_ENV_SMB "\\|/ $%&()-:;<>?@^{}[]`~#./,*!\'\""
# define SHARE_SMB " \t\r\a"

typedef struct		s_env
{
	int				line;
	int				pos;
	int				str_pos;
	char			*str;
}					t_env;

typedef struct		s_pars
{
	int				pos;
	char			*status;
	struct s_env	*ps_env;
}					t_pars;

typedef struct		s_token
{
	int				type_func;
	char			*cmd;
	char			**args;
	char			**redirect;
	int				pipe;
	char			*tmp; 
	char			*tmp2;
	int				flag_n;
}					t_token;

typedef struct		s_all
{
	int				syntax; // bash: syntax error near unexpected token `;;'
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
	char			*home;
	t_token			*tok;
	t_pars			*ps; // структура для парсинга
}					t_all;

/*
**  parsing
*/
int					parsing(t_all *all, t_pars *ps);
int					arguments(t_all *all, char *line, t_pars *ps);

int					quote_no(t_all *all, char *line, t_token *tok, int redir_ignor);
int					quote_one(char *line, t_token *tok, t_pars *ps);
int					quote_two(t_all *all, char *line, t_token *tok, t_pars *ps);

int					redirect(t_all *all, char *line, t_token *tok);
void				command(t_token *tok);




t_all				*clear_all();
void				clear_parsing(t_pars *ps, int clear_place);






int					check_gnl_line(t_all *all, char *str);
int					is_env(char *line, t_pars *ps, char **env);
void				check_env(char *line, t_env *ps_env, char **env);


void				check_shield_no(char *line, t_pars *ps);
void				check_shield_two(char *line, t_pars *ps);

void				create_bin_tok(t_token *tok);

/*
**  execute
*/
int					execute(t_all *all);
char				**save_env(char **envp, int size);
char				*search_env(char **env, char *to_find);
void				ft_free_array(char **to_free);
int					launch(t_all *all);
int					shell_exit(t_all *all);
int					shell_cd(t_token *token, char **env, t_all *all);
int					shell_pwd(void);
int					shell_echo(t_token *token, t_all *all);
int					shell_export(t_token *token, t_all *all);
int					shell_env(char **env);
int					shell_unset(t_token *token, char **env);
#endif
