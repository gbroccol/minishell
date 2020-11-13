/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 12:44:42 by gbroccol          #+#    #+#             */
/*   Updated: 2020/11/12 12:44:44 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_file(char *str, t_token *tok)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	write(1, "bash: syntax error near unexpected token `", 42);
	write(1, str, ft_strlen(str));
	write(1, "'\n", 2);
	tok->er_redir = 1;
	return (1);
}

int			redirect(t_all *all, char *line, t_token *tok)
{
	tok->tmp = NULL;
	tok->er_redir = 0;
	while (line[all->ps->pos] == '>' || line[all->ps->pos] == '<')
	{
		tok->tmp = ft_letter_to_str(tok->tmp, line[all->ps->pos], 0);
		all->ps->pos++;
	}
	tok->redirect = ft_str_to_array(tok->redirect, tok->tmp);
	while (is_smb_in_str(line[all->ps->pos], SHARE_SMB, 0))
		all->ps->pos++;
	tok->tmp = NULL;
	while (is_smb_in_str(line[all->ps->pos], ";|<> ", 1) == 0)
	{
		if (line[all->ps->pos] == '\'')
			quote_one(line, tok, all->ps);
		else if (line[all->ps->pos] == '\"')
			quote_two(all, line, tok, all->ps);
		else
			quote_no(all, line, tok);
	}
	if (is_smb_in_str(line[all->ps->pos], "<>", 0) && check_file(tok->tmp, tok))
		return (1);
	tok->redirect = ft_str_to_array(tok->redirect, tok->tmp);
	tok->tmp = NULL;
	return (0);
}
