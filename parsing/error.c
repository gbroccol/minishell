# include "../minishell.h"

void		error(char *str)
{
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
}