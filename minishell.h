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





typedef struct		s_tokens
{
	int				type_func;
	char			*arg;
	int				quote;
	int				flag;
	int				redir_right;
	int				redir_2right;
	int				redir_left;
	char			*file;
	struct s_tokens		*next;
}					t_tokens;




/*
**  split_line
*/
int					parsing(char *line, t_tokens *tok, int ret_parsing);

/*
**  launch
*/
int					execute(t_tokens *tokens);
int					lsh_num_builtins();
// int					launch(t_tokens *tokens);

// int                 lsh_cd(char **args);
// int                 lsh_help();
// int                 lsh_exit();
int 				lsh_exit();
int 				lsh_cd(t_tokens *token);
int 				lsh_pwd(void);
int 				lsh_echo(t_tokens *token);

#endif