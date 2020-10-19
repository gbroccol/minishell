# include "../minishell.h"




/*
  Объявление функций для встроенных команд оболочки:
 */
int lsh_cd(char **args);
// int lsh_help(char **args);
// int lsh_exit(char **args);
int lsh_help();
int lsh_exit();

/*
  Список встроенных команд, за которыми следуют соответствующие функции
 */
char *builtin_str[] = {
  "cd",
  "help",
  "exit"
};

int (*builtin_func[]) (char **) = {
  &lsh_cd,
  &lsh_help,
  &lsh_exit
};

int lsh_num_builtins() {
  return sizeof(builtin_str) / sizeof(char *);
}

/*
  Реализации встроенных функций
*/
int lsh_cd(char **args)
{
  if (args[1] == NULL) {
    fprintf(stderr, "lsh: ожидается аргумент для \"cd\"\n");
  } else {
    if (chdir(args[1]) != 0) {
      perror("lsh");
    }
  }
  return 1;
}

// int lsh_help(char **args)
int lsh_help()
{
  int i;
  printf("LSH Стивена Бреннана\n");
  printf("Наберите название программы и её аргументы и нажмите enter.\n");
  printf("Вот список втсроенных команд:\n");

  for (i = 0; i < lsh_num_builtins(); i++) {
    printf("  %s\n", builtin_str[i]);
  }

  printf("Используйте команду man для получения информации по другим программам.\n");
  return 1;
}

int lsh_exit()
{
  return 0;
}


int lsh_execute(char **args)
{
  int i;

  if (args[0] == NULL) {
    // Была введена пустая команда.
    return 1;
  }

  for (i = 0; i < lsh_num_builtins(); i++) {
    if (strcmp(args[0], builtin_str[i]) == 0) {
      return (*builtin_func[i])(args);
    }
  }

  return lsh_launch(args);
}
