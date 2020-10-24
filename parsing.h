#ifndef PARSING_H
# define PARSING_H

/*
** Parsing utils
*/

// int		check_envv_and_size(char **str, int *size);
// int		check_envv_and_move(char **str, char **data);
// int		add_envv_and_move(char **ptr, char **str);
// int		count_envv_variable(char **ptr);
// char	*strdup_to_sep(char **ptr);

/*
** Get data for arguments and parsing names
*/

// char	*get_data(char **str);
// char	*get_data_one_space(char **str);
// char	*get_data_no_space(char **str);

/*
** General parsing
*/

// int		parsing_command(t_minishell *minishell);

/*
** Parsing commands
*/

// int		parsing_bin(char **line, t_minishell *minishell);
// int		parsing_cd(char **line, t_lstcommands **commands);
// int		parsing_echo(char **line, t_lstcommands **commands);
// int		parsing_env(char **line, t_lstcommands **commands);
// int		parsing_exit(char **line, t_lstcommands **commands);
// int		parsing_export(char **line, t_lstcommands **commands);
// int		parsing_pipe(char **line, t_lstcommands **commands);
// int		parsing_pwd(char **line, t_lstcommands **commands);
// int		parsing_redirect_double_output(char **line, t_lstcommands **commands);
// int		parsing_redirect_input(char **line, t_lstcommands **commands);
// int		parsing_redirect_simple_output(char **line, t_lstcommands **commands);
// int		parsing_unset(char **line, t_lstcommands **commands);
// int		parse_bin_path(t_minishell *minishell);

#endif