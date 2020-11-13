/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvivian <pvivian@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 15:11:35 by pvivian           #+#    #+#             */
/*   Updated: 2020/11/13 14:00:51 by pvivian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	echo_n(t_token *token)
{
	int		i;
	int		j;

	i = 1;
	while (token->args[i] != NULL)
	{
		j = 0;
		if (token->args[i][j] == '-')
		{
			j++;
			while (token->args[i][j] == 'n')
				j++;
			if (token->args[i][j] == '\0')
			{
				token->flag_n = 1;
				token->args = ft_del_str_from_ar(token->args, i);
				i--;
			}
			else
				return ;
		}
		else
			return ;
		i++;
	}
}

int			shell_echo(t_token *tokens)
{
	int i;

	echo_n(tokens);
	i = 1;
	if (tokens->args[i])
	{
		while (tokens->args[i] != NULL)
		{
			write(1, tokens->args[i], ft_strlen(tokens->args[i]));
			if (tokens->args[i + 1] != NULL)
				write(1, " ", 1);
			i++;
		}
	}
	if (tokens->flag_n == 0)
		write(1, "\n", 1);
	return (0);
}
