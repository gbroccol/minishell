#ifndef ERRORS_H
# define ERRORS_H

# define WRONG_ARG -2
# define TOO_MANY_ARGS -3
# define NOT_ENOUGH_ARGS -4
# define CMD_NOT_FOUND -5
# define ERR_PIPE -6
# define ERR_MALLOC -7
# define ERR_WRITE -8
# define NO_SUCH_FILE -9
# define PERM_DENIED -10
# define IS_A_DIRECTORY -11

# define MSG_CMD_NOT_FOUND "Command not found"
# define MSG_WRONG_ARGS "Wrong argument"
# define MSG_NOT_ENOUGH_ARGS "Not enough arguments"
# define MSG_TOO_MANY_ARGS "Too many arguments"
# define MSG_NO_SUCH_FILE_OR_DIR "No such file or directory"
# define MSG_PERM_DENIED "Permission denied"
# define MSG_IS_A_DIRECTORY "Is a directory"

/*
** Errors about command
*/

// int		command_error(char *name, char *cmd_name, int ret);
// int		write_msg_error(char *prg_name, char *cmd_name, char *msg);
// int		check_too_many_args(char **str, int nb_args_max);

#endif