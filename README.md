# minishell

Minishell is a simple implementation of a shell in C. It demonstrates the basics of how a shell works.

Commands must be on a single line.
Arguments must be separated by whitespace.
No quoting arguments or escaping whitespace.
No piping or redirection.
Only builtins are: cd, help, exit.

-> git branch -a
    # какие ветки существуют
-> git branch -v
    # показать список веток и последний коммит в каждой
-> git branch <branch_new_name> 5589877
    # создать новую ветку с указанным именем на указанном коммите 
-> git checkout <branch_name>
    # перейти на указанную ветку
-> git add
-> git commit -m "..."
-> git push origin <branch_name>
-> git pull