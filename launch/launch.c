# include "../minishell.h"
#include <errno.h> // errno
#include <string.h> //strerror

int launch(t_env *env/*, t_tokens *tokens*/)
{
	pid_t pid;
	int status;

	char *str[] = {"/bin/ls", "-la", NULL}; //
	pid = fork();
	if (pid == 0) 
	{
		if (execve(str[0], str, env->array) == -1)
		{
      		write(1, strerror(errno), ft_strlen(strerror(errno)));
			write(1, "\n", 1);
			exit(EXIT_FAILURE);
		}
  	}
	else if (pid < 0)
	{
		write(1, strerror(errno), ft_strlen(strerror(errno)));
		write(1, "\n", 1);
  	}
	else
	{
		waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
     		waitpid(pid, &status, WUNTRACED);
  	}
	return (1);
}