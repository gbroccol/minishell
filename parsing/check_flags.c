# include "../minishell.h"

void				check_flags(char *line, t_pars *ps, t_tokens *tok)
{
	int			flag;

	flag = ps->pos;
	while (line[ps->pos] == ' ' || line[ps->pos] == '\t')
			ps->pos++;
	if (tok->type_func == 3)
	{
		while (line[ps->pos] == '-')
		{
			if (line[ps->pos] == '-' && line[ps->pos + 1] == 'n')
			{
				tok->flag_n = 1;
				ps->pos = ps->pos + 2;
				while (line[ps->pos] == 'n')
					ps->pos++;
				if (line[ps->pos] != ' ' && line[ps->pos] != '\t')
				{
					ps->pos = flag;
					return ;
				}
				while (line[ps->pos] == ' ' || line[ps->pos] == '\t')
					ps->pos++;
			}
		}
	}
	else
	{
		flag = 0;
		
		while (line[ps->pos] == '-')
		{
			if (flag == 0)
			{
				tok->flags = ft_letter_to_str(tok->flags, line[ps->pos], 1);
				flag = 1;
			}
			ps->pos++;
			while (ft_isalpha(line[ps->pos]))
			{
				tok->flags = ft_letter_to_str(tok->flags, line[ps->pos], 1);
				ps->pos++;
			}
			while (line[ps->pos] == ' ' || line[ps->pos] == '\t')
				ps->pos++;
		}
	}
	return ;
}
