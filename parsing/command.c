/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 19:31:56 by gbroccol          #+#    #+#             */
/*   Updated: 2020/11/20 15:31:04 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void		choose_com(t_token *tok, char *cmd)
{
	if (cmd == NULL)
		tok->type_func = TYPE_NO;
	else if ((ft_strncmp(cmd, "cd", 3)) == 0)
		tok->type_func = TYPE_CD;
	else if ((ft_strncmp(cmd, "pwd", 4)) == 0)
		tok->type_func = TYPE_PWD;
	else if ((ft_strncmp(cmd, "echo", 5)) == 0)
		tok->type_func = TYPE_ECHO;
	else if ((ft_strncmp(cmd, "exit", 5)) == 0)
		tok->type_func = TYPE_EXIT;
	else if ((ft_strncmp(cmd, "export", 7)) == 0)
		tok->type_func = TYPE_EXPORT;
	else if ((ft_strncmp(cmd, "env", 4)) == 0)
		tok->type_func = TYPE_ENV;
	else if ((ft_strncmp(cmd, "unset", 6)) == 0)
		tok->type_func = TYPE_UNSET;
	else
		tok->type_func = TYPE_BIN;
}

int				command(t_token *tok)
{
	int			index;

	if (tok->args != NULL && tok->args[0] != NULL)
	{
		if (!(tok->cmd = ft_strdup(tok->args[0])))
			return (-1);
		index = 0;
		if (tok->args[0][0] == '=' || ft_isdigit(tok->args[0][0]) ||
				check_env_key(tok->args[0]) || !ft_strchr(tok->args[0], '='))
		{
			if (ft_strcmp(tok->args[0], "CD") != 0 &&
					ft_strcmp(tok->args[0], "EXPORT") != 0 &&
					ft_strcmp(tok->args[0], "UNSET") != 0)
			{
				while (tok->args[0][index] != '\0')
				{
					tok->args[0][index] = ft_tolower(tok->args[0][index]);
					index++;
				}
			}
		}
		choose_com(tok, tok->args[0]);
	}
	return (0);
}
