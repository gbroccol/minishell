Allowed functions:

malloc, free
write, open, read, close
fork, wait, waitpid, wait3, wait4
signal, kill
exit
getcwd,
chdir
stat, lstat, fstat
execve
dup, dup2
pipe,
opendir, readdir, closedir
strerror, errno


Your shell should:
+ Show a prompt when waiting for a new command
+ Search and launch the right executable (based on the PATH variable or by using relative or absolute path) like in bash
• It must implement the builtins like in bash:
	• echo with option ’-n’
	+ cd with only a relative or absolute path
	+ pwd without any options
	+ export without any options
	+ unset without any options
	+ env without any options and any arguments
	+ exit without any options
+ ; in the command should separate commands like in bash
+ ’ and "" should work like in bash except for multiline commands
• Redirections < > “>>” should work like in bash except for file descriptor aggregation
+ Pipes | should work like in bash
+ Environment variables ($ followed by characters) should work like in bash
+ $? should work like in bash
• ctrl-C, ctrl-D and ctrl-\ should have the same result as in bash


• Leaks
• Norm
• Error management
• Redirects
• Check if environmental variables are valid
• Protect mallocs (strdups, strjoins etc);
• Добавить замену PWD и OLDPWD в cd
• Добавить передачу кодов выхода из встроенных команд в all->status
• Протестить exit статусы на маке с разными аргументами и добавить в код