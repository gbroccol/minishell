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
  return (0);
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
	if (tokens->redir != NULL)
	{
		if ((ft_strncmp(tokens->redir, ">>", 3)) == 0)
			fd = open(tokens->file, O_RDWR | O_CREAT | O_APPEND, 0666);
		if ((ft_strncmp(tokens->redir, ">", 2)) == 0)
			fd = open(tokens->file, O_RDWR | O_CREAT, 0666);
		// обработать ошибку, если редирект есть но файл не подали
	}		
	if (fd < 0)
	{
		strerror(errno);
		return (1);
	}
	if (tokens->arg)
	{
		write(fd, tokens->arg, ft_strlen(tokens->arg));
		free(tokens->arg);
	}
	if (tokens->flag_n == 0)
		write(1, "\n", 1);
	if (tokens->file)
		free(tokens->file);
	if (fd != 1)
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

int execute(t_tokens *tokens)
{
	int ret;

	ret = 1;
	if (tokens->type_func == -1) 
    	return (ret);
	while (tokens)
	{
		if (tokens->type_func == TYPE_CD)
			ret = lsh_cd(tokens);
		else if (tokens->type_func == TYPE_PWD)
			ret = lsh_pwd();
		else if (tokens->type_func == TYPE_ECHO)
			ret = lsh_echo(tokens);
		else if (tokens->type_func == TYPE_EXIT)
			ret = lsh_exit();
		tokens = tokens->next;
	}
	return (ret);
//  return lsh_launch(args);
}
