# include "../minishell.h"

// int launch(t_tokens *tokens)
// {
// //   pid_t pid, wpid;
// //   int status;

// //   pid = fork();
// //   if (pid == 0) {
// //     // Дочерний процесс
// //     if (execvp(args[0], args) == -1) {
// //       perror("lsh");
// //     }
// //     exit(EXIT_FAILURE);
// //   } else if (pid < 0) {
// //     // Ошибка при форкинге
// //     perror("lsh");
// //   } else {
// //     // Родительский процесс
// //     do {
// //       wpid = waitpid(pid, &status, WUNTRACED);
// //     } while (!WIFEXITED(status) && !WIFSIGNALED(status));
// //   }

//   return 1;
// }