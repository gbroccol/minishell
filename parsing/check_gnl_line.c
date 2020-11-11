#include "../minishell.h"

static int check_str_pipe(char *str)
{
	int i;

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

static void check_err(t_error *er, char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0') // check command
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (str[i] == ';' || str[i] == '|')
		{
			er->syntax = 1;
			return;
		}
		while (str[i] != ';' && str[i] != '|' && str[i] != '\0')
		{
			if (str[i] == '\'')
			{
				i++;
				while (str[i] != '\'' && str[i] != '\0')
					i++;
				if (str[i] == '\'')
					i++;
			}
			else if (str[i] == '\"')
			{
				i++;
				while (str[i] != '\"' && str[i] != '\0')
					i++;
				if (str[i] == '\"')
					i++;
			}
			else
				i++;
		}
		if (str[i] == ';')
		{
			i++;
		}
		else if (str[i] == '|')
		{
			i++;
			if (str[i] == '|')
				i++;
		}
	}
}

int check_gnl_line(t_error *er, char *str)
{
	check_err(er, str);
	if (check_str_pipe(str) == 0)
		return (0);
	return (1);
}