/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 19:29:19 by gbroccol          #+#    #+#             */
/*   Updated: 2020/11/11 19:29:20 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

// void				check_flags(char *line, t_pars *ps, t_token *tok, char **env)
// {
// 	int			flag;

// 	flag = ps->pos;
// 	while (line[ps->pos] == ' ' || line[ps->pos] == '\t')
// 			ps->pos++;
// 	if (tok->type_func == 3)
// 	{
// 		while (line[ps->pos] == '-')
// 		{
// 			if (line[ps->pos + 1] == 'n')
// 			{
// 				tok->flag_n = 1;
// 				ps->pos = ps->pos + 2;
// 				while (line[ps->pos] == 'n')
// 					ps->pos++;
// 				if (line[ps->pos] != ' ' && line[ps->pos] != '\t')
// 				{
// 					ps->pos = flag;
// 					return ;
// 				}
// 				while (line[ps->pos] == ' ' || line[ps->pos] == '\t')
// 					ps->pos++;
// 			}
// 			else if (line[ps->pos + 1] == '$')
// 			{
// 				is_env(line, ps, env);
				
// 				if (ps->ps_env->str != NULL)
// 					if ((ft_strncmp(ps->ps_env->str, "n", 2)) == 0)
// 					{
// 						tok->flag_n = 1;
// 						// ps->pos = ;
// 						while (line[ps->pos] == 'n')
// 							ps->pos++;
// 					}
					
// 				// if (line[ps->pos] != ' ' && line[ps->pos] != '\t')
// 				// {
// 				// 	ps->pos = flag;
// 				// 	return ;
// 				// }
// 				while (line[ps->pos] == ' ' || line[ps->pos] == '\t')
// 					ps->pos++;
// 			}
// 			else
// 				break ;
// 		}
// 	}
// 	else
// 	{
// 		flag = 0;
// 		while (line[ps->pos] == '-')
// 		{
// 			if (flag == 0)
// 			{
// 				tok->flags = ft_letter_to_str(tok->flags, line[ps->pos], 1);
// 				flag = 1;
// 			}
// 			ps->pos++;
// 			while (ft_isalpha(line[ps->pos]))
// 			{
// 				tok->flags = ft_letter_to_str(tok->flags, line[ps->pos], 1);
// 				ps->pos++;
// 			}
// 			while (line[ps->pos] == ' ' || line[ps->pos] == '\t')
// 				ps->pos++;
// 		}
// 		tok->args = ft_str_to_array(tok->args, tok->flags);


// 		tok->flags = NULL;
// 	}
// 	return ;
// }
