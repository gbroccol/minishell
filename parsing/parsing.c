# include "../minishell.h"

t_token		*clear_tokens()
{
	t_token	*tok;

	if (!(tok = (t_token *)malloc(sizeof(t_token))))
			return (NULL);  // обработать ошибку
	tok->type_func = -1;
	tok->cmd = NULL;
	tok->arg = NULL;
	tok->args = NULL;
	tok->flags = NULL;
	tok->pipe = 0;
	tok->redir = NULL;
	tok->file = NULL;
	tok->flag_n = 0;
	tok->bin_tok = NULL;
	tok->redirect = NULL;
	return (tok);
}

int				parsing(t_all *all, t_pars *ps)
{
	int			pars_ret;
	// int			index;

	pars_ret = 1;
	all->tok = clear_tokens();
	while (check_divide(all->gnl_line[ps->pos], " \t\r\a", 1))
		ps->pos++;
	if (all->gnl_line[ps->pos] != '\0')
	{
		all->wait_cmd = 0;
		all->tok->args = NULL;
		if (all->gnl_line[ps->pos] == '>' || all->gnl_line[ps->pos] == '<')
			check_redirect(all->gnl_line, ps, all->tok, all->env);
		command(all->gnl_line, all->tok, ps, all->env);
		// check_flags(all->gnl_line, ps, all->tok, all->env);
		pars_ret = arguments(all, all->gnl_line, all->tok, ps, all->env);


		// if (all->tok->type_func == TYPE_BIN)
		// {
		// 	if (all->tok->redirect != NULL)
		// 	{
		// 		index = 0;
		// 		while (all->tok->redirect[index] != NULL)
		// 		{
		// 			all->tok->args = ft_str_to_array(all->tok->args, all->tok->redirect[index]);
		// 			all->tok->redirect[index] = NULL;
		// 			index++;
		// 		}
		// 		free(all->tok->redirect);
		// 		all->tok->redirect = NULL;
		// 	}
		// }


		if (pars_ret == 0) // для комментария
			return (0);

		if (all->gnl_line[ps->pos] != '\0')
			return (1);
	}
	return (0);
}
