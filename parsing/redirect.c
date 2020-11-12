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

int		redirect(t_all *all, char *line, t_token *tok)
{
	tok->tmp = NULL;
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
			quote_no(all, line, tok, 1);
	}
	tok->redirect = ft_str_to_array(tok->redirect, tok->tmp);
	tok->tmp = NULL;
	return (1);
}
