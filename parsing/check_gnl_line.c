#include "../minishell.h"

static int		check_str_pipe(char *str)
{
	int			i;

	i = 0;
	if (str && str[i] != '\0')
	{
		while (str[i] != '\0')
			i++;
		while (i > 0 && (str[i] == '\0' || str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r')))
			i--;
		if (str[i] == '|')
			return (1);
		return (0);
	}
	return (0);
}

static int		check_err_str(t_error *er, char *str, int i)
{
	// int			smb1;
	// int			smb2;

	// smb1 = ';';
	// smb2 = '|';
	while (str[i] != '\0' && str[i] != '\'' && str[i] != '\"' && str[i] != '#')
	{
		if (str[i] == ';')
		{
			i++;
			while (str[i] == ' ' || str[i] == '\t')
				i++;
			if (str[i] == ';')
			{
				// write(1, "error\n", 6);
				er->syntax = 1;
				er->token = ft_strdup(";;");
				return (-1);
			}
		}
		i++;
	}
	return (i);
}

static void		check_err(t_error *er, char *str)
{
	int			i;

	i = 0;
	while (i != -1 && str[i] != '\0')
	{
		if (str[i] == '\'')
		{
			while (str[i] != '\0' && str[i] != '\'')
				i++;
			continue ;
		}
		else if (str[i] == '\"')
		{
			while (str[i] != '\0' && str[i] != '\"')
				i++;
			continue ;
		}
		else if (str[i] == '#')
			break ;
		else
			i = check_err_str(er, str, i);
	}
}

int				check_gnl_line(t_error *er, char *str)
{
    if (check_str_pipe(str) == 0)
    {
        check_err(er, str);
        return (0);
    }
    return (1);
}