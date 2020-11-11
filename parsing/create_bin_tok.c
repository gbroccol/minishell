/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_bin_tok.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 19:32:28 by gbroccol          #+#    #+#             */
/*   Updated: 2020/11/11 19:32:29 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

#include <stdio.h>

void		create_bin_tok(t_token *tok)
{
	int		i;

	i = 0;
	if (tok->cmd != NULL)
		i++;
	if (tok->flags != NULL)
		i++;
	if (tok->arg != NULL)
		i++;
	
	if (!(tok->bin_tok = (char **)malloc(sizeof(char *) * i + 1)))
		return ; // error

	i = 0;
	if (tok->cmd != NULL)
	{
		tok->bin_tok[i] = tok->cmd;
		i++;
	}
	if (tok->flags != NULL)
	{
		tok->bin_tok[i] = tok->flags;
		i++;
	}
	if (tok->arg != NULL)
	{
		tok->bin_tok[i] = tok->arg;
		i++;
	}
	tok->bin_tok[i] = NULL;
	// i = 0;

	// while (tok->bin_tok[i] != NULL)
	// {
	// 	printf("%s\n", tok->bin_tok[i]);
	// 	i++;
	// }
}
