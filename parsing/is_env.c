# include "../minishell.h"

int			is_env(char *line, t_pars *ps, char **env)
{
	if (line[ps->pos + 1] != '/' &&	line[ps->pos + 1] != '\\' &&
		line[ps->pos + 1] != ' ' && line[ps->pos + 1] != '\t' &&
		line[ps->pos + 1] != '|' &&	line[ps->pos + 1] != '?' &&
		line[ps->pos + 1] != '.' &&	line[ps->pos + 1] != ',' &&
		line[ps->pos + 1] != ':' &&
		line[ps->pos + 1] != ';') // проверить символы по ASCII
	{
		ps->pos++;
		if (ft_isdigit(line[ps->pos]))
		{
			ps->pos++;
			return (1);
		}
		ps->ps_env->env_line = 0;
		ps->ps_env->env_pos = 0;
		ps->ps_env->str_pos = ps->pos;
		ps->ps_env->str = NULL;
		
		check_env(line, ps->ps_env, env);

		ps->pos = ps->ps_env->str_pos;
		// if (ps->ps_env->str != NULL)
		// 	tmp_line = ft_str_to_str(tmp_line, ps->ps_env->str);
		return (0);
	}
	return (1);
}
		