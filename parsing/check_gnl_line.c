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

// static int		check_err_str(t_error *er, char *str, int i)
// {
// 	// int			smb1;
// 	// int			smb2;

// 	while (str[i] != '\"' && str[i] != '\'' && str[i] != '#'  && str[i] != '\0')
// 	{
// 		while (str[i] == ' ' || str[i] == '\t')
// 			i++;
// 		if (str[i] == ';')
// 		{
// 			i++;
// 			if (str[i] == ';')
// 			{
// 				er->syntax = 1;
// 				er->token = ft_strdup(";;");
// 			return (-1);
// 			}
// 			if (str[i] == '|' || str[i] == '\0')
// 			{
// 				er->syntax = 1;
// 				er->token = ft_strdup(";");
// 				return (-1);
// 			}
// 			while (str[i] == ' ' || str[i] == '\t')
// 				i++;
// 			if (str[i] == ';' || str[i] == '|')
// 			{
// 				er->syntax = 1;
// 				er->token = ft_strdup(";");
// 				return (-1);
// 			}
// 		}
// 		else if (str[i] == '|')
// 		{
// 			i++;
// 			if (str[i] == '|')
// 			{
// 				er->syntax = 1;
// 				er->token = ft_strdup("||");
// 				return (-1);
// 			}
// 			if (str[i] == ';' || str[i] == '\0')
// 			{
// 				er->syntax = 1;
// 				er->token = ft_strdup("|");
// 			return (-1);
// 			}
// 			while (str[i] == ' ' || str[i] == '\t')
// 				i++;
// 			if (str[i] == ';' || str[i] == '|')
// 			{
// 				er->syntax = 1;
// 				er->token = ft_strdup("|");
// 				return (-1);
// 			}
// 		}
// 		else
// 			i++;
// 	}
// 	return (i);
// }

static void		check_err(t_error *er, char *str)
{
	int			i;
	// int			smb;
	// int			start;

	i = 0;
	// start = 0;
	while (str[i] != '\0') // check command
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (str[i] == ';' || str[i] == '|')
		{
			er->syntax = 1;
			return ;
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


	// while (str[i] == ' ' || str[i] == '\t')
	// 	i++;
	// if (str[i] == ';' || str[i] == '|')
	// {
	// 	smb = str[i];
	// 	i++;
	// 	while (str[i] == ' ' || str[i] == '\t')
	// 		i++;
	// 	if (str[i] != ';' && str[i] != '|')
	// 	{
	// 		er->syntax = 1;
	// 		if (smb == ';')
	// 			er->token = ft_strdup(";");
	// 		else if (smb == '|')
	// 			er->token = ft_strdup("|");
	// 		return ;
	// 	}
	// }

	// i = 0;
	// while (i != -1 && str[i] != '\0')
	// {
	// 	if (str[i] == '\'')
	// 	{
	// 		i++;
	// 		while (str[i] != '\0' && str[i] != '\'')
	// 			i++;
	// 		continue ;
	// 	}
	// 	else if (str[i] == '\"')
	// 	{
	// 		i++;
	// 		while (str[i] != '\0' && str[i] != '\"')
	// 			i++;
	// 		continue ;
	// 	}
	// 	else if (str[i] == '#')
	// 		break ;
	// 	else
	// 		i = check_err_str(er, str, i);
	// }
	// if (i == -1)
	// 	return (-1);
	// return (0);
}


int				check_gnl_line(t_error *er, char *str)
{
	check_err(er, str);
    if (check_str_pipe(str) == 0)
        return (0);
    return (1);
}