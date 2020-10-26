#include "../minishell.h"
#include <sys/param.h>
#include <errno.h>

// typedef struct      s_tokens
// {
//     int             type_func;
//     char            *arg;
// 	char			*file;
//     int             flag;
//     int             redir_right;
//     int             redir_2right;
//     int             redir_left;
//     t_tokens        *next;
// }                   t_tokens;


/*
  Объявление функций для встроенных команд оболочки:
 */
// int lsh_cd(char **args);
// int lsh_help(char **args);
// int lsh_exit(char **args);
// int lsh_help();
int lsh_exit();
int lsh_cd(t_tokens *token);
int lsh_pwd(void);
int lsh_echo(t_tokens *token);

/*
  Список встроенных команд, за которыми следуют соответствующие функции
 */
// char *builtin_str[] = {
//   "cd",
//   "help",
//   "exit"
// };

// int (*builtin_func[]) (char **) = {
//   &lsh_cd,
//   &lsh_help,
//   &lsh_exit
// };

// int lsh_num_builtins() {
//   return sizeof(builtin_str) / sizeof(char *);
// }

/*
  Реализации встроенных функций
*/

// int lsh_cd(char **args)
// {
//   if (args[1] == NULL) {
//     fprintf(stderr, "lsh: ожидается аргумент для \"cd\"\n");
//   } else {
//     if (chdir(args[1]) != 0) {
//       perror("lsh");
//     }
//   }
//   return 1;
// }

// int lsh_help(char **args)
// int lsh_help()
// {
//   int i;
//   printf("LSH Стивена Бреннана\n");
//   printf("Наберите название программы и её аргументы и нажмите enter.\n");
//   printf("Вот список втсроенных команд:\n");

//   for (i = 0; i < lsh_num_builtins(); i++) {
//     printf("  %s\n", builtin_str[i]);
//   }

//   printf("Используйте команду man для получения информации по другим программам.\n");
//   return 1;
// }

int lsh_exit()
{
  return 0;
}

int lsh_cd(t_tokens *tokens)
{

	// if (!tokens->arg)
	// 	write(1, $HOME, ft_strlen($HOME));
 	// else 
	// {
    if (chdir(tokens->arg) != 0)
      strerror(errno);
	free(tokens->arg);
//   }
  return (1);
}

int lsh_pwd(void)
{
	char dir[MAXPATHLEN];

	getcwd(dir, MAXPATHLEN);
	write(1, dir, ft_strlen(dir));
	write(1, "\n", 1);
	return (1);
}

int lsh_echo(t_tokens *tokens)
{
	int fd;

	fd = 1;
	if (tokens->redir_right == 1)
		fd = open(tokens->file, O_RDWR | O_CREAT, 0666);
	if (tokens->redir_2right == 1)
		fd = open(tokens->file, O_RDWR | O_CREAT | O_APPEND, 0666);
	if (fd < 0)
	{
		strerror(errno);
		return (0);
	}
	if (tokens->arg)
	{
		write(fd, tokens->arg, ft_strlen(tokens->arg));
		free(tokens->arg);
	}
	if (tokens->flag != 'n')
		write(1, "\n", 1);
	free(tokens->arg);
	if (tokens->file)
		free(tokens->file);
	close(fd);
	return(1);
}

// int lsh_execute(char **args)
// {
//   int i;

//   if (args[0] == NULL) {
//     // Была введена пустая команда.
//     return 1;
//   }

//   for (i = 0; i < lsh_num_builtins(); i++) {
//     if (strcmp(args[0], builtin_str[i]) == 0) {
//       return (*builtin_func[i])(args);
//     }
//   }

//   return lsh_launch(args);
// }

int lsh_execute(t_tokens *tokens)
{
	if (tokens->type_func == -1) 
	{
    // Была введена пустая команда.
		write (1, "\n", 1);
    	return (1);
	}

	while (tokens)
	{
		if (tokens->type_func == 1)
			lsh_cd(tokens);
		else if (tokens->type_func == 2)
			lsh_pwd();
		else if (tokens->type_func == 3)
			lsh_echo(tokens);
		else if (tokens->type_func == 4)
			lsh_exit();
		tokens = tokens->next;
	}
	return (1);
//  return lsh_launch(args);
}