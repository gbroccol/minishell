# include "../minishell.h"

int				check_redirect(char *line, int pos, t_tokens *tok)
{
	while (line[pos] == '>' || line[pos] == '<')
	{
		tok->redir = ft_letter_to_str(tok->redir, line[pos], 0);
		pos++;	
	}
	while (line[pos] == ' ' || line[pos] == '\t')
		pos++;
	while (line[pos] != ' ' && line[pos] != '\t' && line[pos] != '\0')
	{
		tok->file = ft_letter_to_str(tok->file, line[pos], 0);
		pos++;	
	}
	while (line[pos] == ' ' || line[pos] == '\t')
		pos++;
	return (pos);
}