#ifndef MINISHELL_H
# define MINISHELL_H

# include "errors.h"
# include "parsing.h"


# include <unistd.h> // write, open, read, close, chdir, fork, exec - ???, pid_t - ???
# include <stdlib.h> // malloc, free, realloc - NO, exit, execvp - NO, EXIT_SUCCESS, EXIT_FAILURE
# include <sys/types.h> // wait
	// fork - 
	// wait -
#include <sys/wait.h> // waitpid() и связанные макросы
	// waitpid - 
# include <math.h>
# include <fcntl.h>
# include "./libft/libft.h"

#include <stdio.h>            // remove fprintf(), printf(), stderr, getchar(), perror()
#include <string.h>           // remove strcmp(), strtok()
//  wait3, wait4, signal, kill, , getcwd,
// , stat, lstat, fstat, execve, dup, dup2, pipe,
// opendir, readdir, closedir, strerror, errno

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

typedef struct			s_env
{
	int					env_line;
	int					env_pos;
	int					str_pos;
	char				*str;
}						t_env;

typedef struct			s_pars
{
	int					pos; // for gnl_line
	int					tmp_pos;
	int					index;
	int					quote_start;
	int					quote_finish;
	int					space;
	struct s_env		*ps_env;
}						t_pars;

typedef struct			s_tokens  // каждый лист замолочен
{
	int					type_func;
	char				*cmd; // command text if error (there is no such command) // malloc
	char				*flags;
	char				*arg; // malloc
	int					pipe;
	char				*redir;
	char				*file; // malloc
	int					flag_n;
	char				**bin_tok; // malloc
	struct s_tokens		*next; // malloc
}						t_tokens;

typedef struct			s_all
{
	int					ret_ex;
	int					ret_pars;
	char				*gnl_line;
	char				**env;
	t_tokens			*toks;
	t_pars				*ps; // структура для парсинга
}						t_all;

/*
**  split_line
*/
t_all					*clear_all();
void					clear_parsing(t_pars *ps, int clear_place);
int						parsing(t_all *all, t_tokens **toks, t_pars *ps);
void					command(char *line, t_tokens *tok_next,	t_tokens *toks, t_pars *ps);
int						arguments(char *line, t_tokens *tok, t_pars *ps, char **env);
int						quote_no(char *line, t_tokens *tok, t_pars *ps, char **env);
int						quote_one(char *line, t_tokens *tok, t_pars *ps);
int						quote_two(char *line, t_tokens *tok, t_pars *ps, char **env);
void					check_flags(char *line, t_pars *ps, t_tokens *tok);
void					check_env(char *line, t_env *ps_env, char **env);
int						check_redirect(char *line, int pos, t_tokens *tok);
char					*check_shielding(char *line);
void					create_bin_tok(t_tokens *tok);

/*
**  launch
*/
int					execute(t_tokens *tokens, char **env);
int					lsh_num_builtins();
// int					launch(t_tokens *tokens);

// int                 lsh_cd(char **args);
// int                 lsh_help();
// int                 lsh_exit();
int 				lsh_exit();
int 				lsh_cd(t_tokens *token, char **env);
int 				lsh_pwd(void);
int 				lsh_echo(t_tokens *token);

#endif