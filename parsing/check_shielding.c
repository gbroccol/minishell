/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_shielding.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 19:30:14 by gbroccol          #+#    #+#             */
/*   Updated: 2020/11/11 19:30:15 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void        check_shielding(char *line, t_pars *ps)
{
    if (line[ps->pos] == '\\' && line[ps->pos + 1] == '$')
        ps->pos++;
    else if (line[ps->pos] == '\\' && line[ps->pos + 1] == '\"')
        ps->pos++;
    else if (line[ps->pos] == '\\' && line[ps->pos + 1] == '\\')
        ps->pos++;
    else if (line[ps->pos] == '\\' && line[ps->pos + 1] == '`')
        ps->pos++;

}
