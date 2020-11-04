#! /bin/bash

###############################################################################################
'Hello World!'                                                       # - НАСТЯ
echo 'Hello World!'                                              # +
echo jbkjnk                                                      # +
echo abc def                                                     # +
echo abc             def                                         # +
     echo    890     345                                         # +
ECHO 1223                                                           # - НАСТЯ
echo "123" "456"                                                 # +
echo "$"                                                         # +
echo "$/"                                                        # +
echo "$'"                                                        # +
echo "$ "                                                        # +

echo "$$"                                                            # - НАСТЯ

echo "\$" '\$' \$                                                # +
echo "$|$"                                                       # +
echo -n 55                                                       # +
echo -n ''                                                       # +
echo -n 'jbbjhhd'                                                # +
echo 123 ;                                                       # +
echo 123 ; echo 456                                              # +
echo "42 ;" ; echo "24 24"                                       # +
echo -n -n -n 23                                                 # +
echo "\$ \#     |$/\n"                                           # +    
echo "\$|$/"                                                     # +
echo "Это #не комментарий"                                       # +
echo Это # Вот комментарий.                                          # - кириллица работает через раз
echo This              is # comment                              # +
echo Это \# не комментарий                                       # +
echo 567t6 ; 890 -n mk ; echo 123                                # +
echo 567t6 ; 890                                                 # +
echo Это # комментарий                                           # +
echo 123 ; echo Это \# не комментарий                            # +
# пустая строка                                                  # +
echo $LOGNAME                                                    # +
echo $LOGNAME\ууу                                                # +
echo $LOGNAME/ууу                                                # +

echo "123 $LOGNAME 456"                                          # +
echo "123 $LOGNAMEeee 456"                                       # +
echo "$LOGNAME/eee"                                              # +

echo '$LOGNAME/eee'                                              # +
echo '$LOGNAME\eee   |'                                          # +
echo '$PWD'                                                      # +
echo $PWD                                                        # +
echo "$PWD"                                                      # +

echo -n 5 | cat -e                                              # КАТЯ 
echo 5 | cat -e                                                 # КАТЯ
echo "dd" | cat -e                                              # КАТЯ
echo '||' | cat -e                                              # КАТЯ
echo 42 23 | grep 4 | cat -e                                    # КАТЯ
ls 1111111 | grep 111 | cat -e                                  # КАТЯ

echo 123 > 1                                                    # +
echo '123 > 2'                                                  # +
echo "123 > 1"                                                  # +
echo > 1                                                        # +
echo "> 1"                                                      # +

echo 42 > 1 ; echo 22 >> 1 ; cat -e  1                          # КАТЯ
grep 2 < 1                                                      # КАТЯ
echo < 1                                                        # - не выводится сообщение об ошибке, если файл не существует КАТЯ
grep < 1                                                        # КАТЯ
grep 4 < 1 | cat -e                                             # КАТЯ

export qwe=123456 ; echo $qwe                                   # КАТЯ
echo "qwe"'qwe'                                                 # +
echo "qwe" 'qwe'                                                # +

ls                                                              # +
./ls                                                            # + скорректировать сообщение об ошибке

# bash: syntax error near unexpected token
# start
;;                                                                              # НАСТЯ
;                                                                               # НАСТЯ
|                                                                               # НАСТЯ
||                                                                              # НАСТЯ
;@@;                                                                            # НАСТЯ
| |                                                                             # НАСТЯ
ls;;                                                                            # НАСТЯ
ls; ;                                                                           # НАСТЯ
ls |                                                                            # НАСТЯ
ls||                                                                            # НАСТЯ
ls | |                                                                          # НАСТЯ
# finish

echo $PWD                                                                       # +
echo $321                                                                       # +

echo $\321                                                                      # +
echo $|                                                                         # -
echo $|cat                                                                      # -
echo $|cat -e                                                                   # -
echo $|321                                                                      # -
echo $;321                                                                      # -
echo $/321                                                                      # +
echo $'321                                                                      # +
'
echo $ 321                                                                      # +
echo $"321                                                                      # +
"
echo "$'321"                                                                    # +

echo $fdsgbkldmbklfdsmklfmd                                                     # +
echo str1"'str2'"                                                               # +
echo str1"'$str2'"                                                              # +
echo 'str1'str2"str3 $PWD str4" "str5"'$PWD' $PWD "$PWD"                        # +
echo "hello><; world"                                                           # +
echo $hfkdghldf$PWD                                                             # +
echo ' """" '                                                                   # +
echo " '''''' "                                                                 # +
echo """"""""                                                                   # +
echo ''''''''                                                                   # +
echo """"""""""              :""                                                # +
echo """""""""",         wtf     :""                                            # +
echo """""""""",         wtf     :""                                            # +
echo '"""""""""",         wtf     :""'                                          # +
echo hello                       happy                               man        # +
export = ; echo $?

echo $?                                                                         # +
echo '$?'                                                                       # +
echo "$?"                                                                       # +
echo $?$PWD                                                                     # +
echo $?$.                                                                       # +
echo $.                                                                         # +
echo $?123                                                                      # +
echo "$?123"                                                                    # +
echo $? | cat - e                                                               # - КАТЯ
echo $? | cat -e                                                                # - КАТЯ
echo $? ; ls ; echo $?...                                                       # +

'e'c"h"o 5                                                                      # +
'echo' 5                                                                        # +
'ec"h"o' 5                                                                      # +

...$?...                                                                        # - КАТЯ
echo $? ; ls ; ...$?...                                                         # - КАТЯ

export str1 2str = _3str str4=str5                                              # - нет сообщений об ошибках, невалидные переменные создались КАТЯ
 'e'"x"p'o'r't'                                                                 # +
ec"ho" $str1 $str4                                                              # - работает неправильно
 'export' 'q'=e "w"=c e="h" r='o' 't'='x' "y"="p" u=r i=t                       # - работает неправильно
  'e'"x"p'o'r't' "t"$q's'$i='h'"e"'l'l$r                                        # - работает неправильно
echo "hello;"; $q'c'"h"o $test                                                  # - 
echo "hello;"; $q'c'"h"o $test                                                  # - 
$q$w$e'o' $PWD;   cd .. ;    $q"c"$e'o' $PWD    ;                               # - работает неправильно
cd -; pwd                                                                       # - сега
$lkjlkjllkdfs$q$w$e$r "$e"$q"l"'l'$r;                                           # - работает неправильно
 echo         \'\"\\                                                            # - сега
echo ~                                                                          # - работает неправильно
echo hello sad man                                                              # +
echo $?
>fil$q'1' e$w"ho" s$i"r"ing f$r$u file1                                         # - работает неправильно
pwd ; cat file1                                                                 # - 
ls lskdgjdhgisdoigjiredg                                                        # + скорректировать сообщение об ошибке КАТЯ
echo $?
echo $?
unset PWD; echo $PWD                                                            # - 
ls; unset PATH; ls     ;                                                        # - работает неправильно
echo $?
echo $?
export PATH=/  ; ls                                                             # - сега
echo $?
export PATH=/bin  ; ls                                                          # - сега
echo $?
echo $PWD; unset PWD                                                            # - работает неправильно
echo $PWD; export PWD=/ ; echo $PWD;                                            # - сега
pwd; echo $PWD                                                                  # - работает неправильно: точка с запятой приклеивается к команде НАСТЯ
cd; echo $PWD; cd -                                                             # - работает неправильно: точка с запятой приклеивается к команде НАСТЯ
echo $PWD; echo $OLDPWD                                                         # - работает неправильно
unset OLDPWD; echo $OLDPWD                                                      # - сега
cd; echo $OLDPWD                                                                # - работает неправильно: точка с запятой приклеивается к команде НАСТЯ
cd ; echo $PWD; echo $OLDPWD                                                    # - сега
cd -                                                                            # - работает неправильно: не считывается '-' при парсинге НАСТЯ
ls -la                                                                          # +
ls "-la" ; cd -                                                                 # - работает неправильно: не считывается '-' при парсинге НАСТЯ
echo '\'                                                                        # +
echo \hello \$PWD                                                               # +
echo '\hello \$PWD'                                                             # +
echo "\hello \$PWD"                                                             # +
echo \'\"\\ "\hello\$PWD"                                                       # +
echo "\$PWD" "\PWD"                                                             # +
echo "\""                                                                       # +
echo "\'"                                                                       # +
"echo f" hello                                                                  # + различаются сообщения об ошибке из-за того, что в качестве команды подается "echo , а не echo f
>"helo l" echo hell\ f                                                          # - работает неправильно
>>"helo l" echo hell\ f ; echo hell\ f                                          # - работает неправильно
export t=n; echo -$t -n "-"'n' hello                                            # - сега
echo -$t "-n" '-''n' '-n;'         -n hello                                     # - работает неправильно
export a=l d=s; $a$d                                                            # - сега
echo $PWD > as ; cat as                                                         # - сега
echo ''\''"a|"\'q'a'\a'w'                                                       # +
echo \"\|\;\"\| cat -e > \q\w\e\r\t\y ; cat qwerty                              # - сега
pwd >a1>a2>a3; echo s1 >q1 s2>q2 s3; cat a2; cat a3; cat q1; cat q2;            # - сега
echo                                                                            # +
echo hello '\' ';' "   '\' \" " \" "$PWD\\\"\~\;"\; >> t1 \' \ \ \\             # - работает неправильно
echo hello '\' ';' "   '\' \" " \" "$PWD\\\"\~\;"\; >> t1 \' \ \ \\ ; cat t1    # - сега
\ls\ ;                                                                          # - работает неправильно
echo ${PATH#*:}                                                                 # - Специальная переменная
echo $(( 2#101011 ))                                                            # - Преобразование системы счисления в арифметической подстановке

echo 123> 1                                                                     # - работает неправильно КАТЯ
echo 123jrd> 3                                                                  # +
echo 123> 3                                                                     # - работает неправильно КАТЯ
# >, >> - перенаправление стандартного вывода программы в файл
# < - перенаправление стандартного ввода программы из файла
# |- перенаправление стандартного вывода программы на стандартный ввод другой программы
# ; Разделитель команд в строке

# ;; Разделитель альтернатив в операторе case
# case "$VARiable" in
# abc) echo "$VARiable = abc" ;;
# xyz) echo "$VARiable = xyz" ;;
# esac

# . Аналог команды source (#include в С++). Выполняет скрипт в текущем интерпретаторе.
# . myconf

# ".." Двойные кавычки, отменяют действие спецсимволов кроме $ `..` и \
# '...' Апострофы, отменяют действие всех спецсимволов в том числе и \, по этому нельзя включить апостроф в строку ограниченную апострофами

# : Нулевая команда, всегда возвращает нулевой код ответа. В сочетании с перенаправлением ">" создает файл, или обнуляет существующий. В сочетании с перенаправлением ">>" создает файл, или изменяет время модификации существующего
# :> data.xxx # File “data.xxx” now empty.
# (можно и без двоеточия)

# Шаблоны в именах файлов. Если подходящие имена находятся, то они подставляются в командную строку как отдельные аргументы (возможно с пробелами внутри). Если имена не находятся, то шаблон остается как есть.

# * Шаблон заменяющий любую последовательность символов
# ? Шаблон заменяющий ровно один символ
# [xyz] Шаблон заменяющий один из перечисленных символов
# {xxx,yyy,zzz,...} Подстановка одного из вариантов в шаблон. В скобках не должно быть неэкранированных пробелов
# grep Linux file*.{txt,htm*} # Ищет слово “Linux” в файлах вида “fileA.txt”, “file2.txt”, “fileR.html”, “file-87.htm”, etc.

# $ Подстановка значения переменной, арифметического выражения или стандартного вывода программы. Если значение содержит пробелы, то при подстановке оно разбивается на отдельные аргументы.
# $A содержимое переменной A
# $$ PID процесса
# $? Код возврата из последней выполненной программы или функции, а также код возврата самого скрипта
# $((2*2)) подстановка результата вычисления арифметического выражения
# $(cmd) подстановка стандартного вывода программы
# `...` тоже, что и $(...) – подстановка стандартного вывода программы

# Пример: A=EE; echo $A $(echo QQ) $((7+5))
# Результат: EE QQ 12
# Ошибка: $A=ZZ
# Результат: bash: EE=ZZ: command not found

# (...) Группировка команд
# (A=hello; echo $A)
# Для выполнения группы в скобках запускается новый интерпретатор
# A=123
# (A=321)
# echo A = $A # A = 123
# # "A" внутри скобок – локальная переменная.

# (...) Создание массива ( только в bash версии > 2)
# Array=(element1 element2 element3)

# [] Элемент массива ( только в bash версии > 2)
# Array[1]=slot_1
# echo ${Array[1]}

# {1..10} - подстановка чисел от 1 до 10
# {c..n} - подстановка символов от "c" до "n"

# {...} Создание безымянной функции, удобно для перенаправления ввода/вывода нескольких команд в один файл. В отличие от настоящей функции видимости переменных не изменяется.
# PACK=mysql
# {
# echo
# echo "Archive Listing:"
# rpm -qpl ${PACK} # Список фалов в пакете rpm
# echo
# rpm -i --test ${PACK} # Проверка, установлен ли пакет.
# } > "${PACK}.txt" #И весь вывод в один файл.

# [...] Встроенная функция test для вычисления логических выражений

# ((...)) Арифметическая подстановка, вычисляет арифметическое выражение в стиле языка Си внутри скобок

# & - запуск программы в фоновом режиме
# bash$ sleep 10 &
# [1] 850
# [1]+ Done sleep 10

###############################################################################################
cd minishell
cd libft
cd ..
cd .
cd ~
cd Desktop


###############################################################################################
pwd
 
###############################################################################################
export

ex $FINAL=5
env

ex $FINAL=BASH
env

FINAL=SUN
export FINAL
env

final=sun
export final
env

###############################################################################################
unset USER42
unset MAIL42

###############################################################################################
env

###############################################################################################
exit
exit 23

###############################################################################################
/bin/ls
/bin/echo 12
ls -la
/bin/ls
echo $?
/bin/ls ffffff
echo $?
/bin/ls ; echo -n 42;echo 42

cat

unset PATH
ls
export PATH=/bin

#################################################################################
;;
;
|
||
;@@;
| |
ls;;
ls; ;
ls |
ls||
ls | |
echo $PWD
echo $321
echo $fdsgbkldmbklfdsmklfmd
echo str1"'str2'"
echo str1"'$str2'"
echo 'str1'str2"str3 $PWD str4" "str5"'$PWD' $PWD "$PWD"
echo "hello><; world"
echo $hfkdghldf$PWD
echo ' """" '
echo " '''''' "
echo """"""""
echo ''''''''
echo """"""""""              :""
echo """""""""",         wtf     :""
echo """""""""",         wtf     :""
echo '"""""""""",         wtf     :""'
echo hello                       happy                               man
export = ; echo $?
echo $?
export str1 2str = _3str str4=str5 
 'e'"x"p'o'r't'
ec"ho" $str1 $str4
 'export' 'q'=e "w"=c e="h" r='o' 't'='x' "y"="p" u=r i=t
  'e'"x"p'o'r't' "t"$q's'$i='h'"e"'l'l$r
echo "hello;"; $q'c'"h"o $test
echo "hello;"; $q'c'"h"o $test
$q$w$e'o' $PWD;   cd .. ;    $q"c"$e'o' $PWD    ;
cd -; pwd
$lkjlkjllkdfs$q$w$e$r "$e"$q"l"'l'$r;
 echo         \'\"\\
echo ~
echo hello sad man
echo $?
>fil$q'1' e$w"ho" s$i"r"ing f$r$u file1
pwd ; cat file1
ls lskdgjdhgisdoigjiredg
echo $?
echo $?
unset PWD; echo $PWD
ls; unset PATH; ls     ;
echo $?
echo $?
export PATH=/  ; ls
echo $?
export PATH=/bin  ; ls
echo $?
echo $PWD; unset PWD
echo $PWD; export PWD=/ ; echo $PWD;
pwd; echo $PWD
cd; echo $PWD; cd -
echo $PWD; echo $OLDPWD
unset OLDPWD; echo $OLDPWD
cd; echo $OLDPWD
cd ; echo $PWD; echo $OLDPWD
cd -
ls -la
ls "-la" ; cd -
echo '\'
echo \hello \$PWD
echo '\hello \$PWD'
echo "\hello \$PWD"
echo \'\"\\ "\hello\$PWD"
echo "\$PWD" "\PWD" 
echo "\""
echo "\'"
"echo f" hello
>"helo l" echo hell\ f
>>"helo l" echo hell\ f ; echo hell\ f
export t=n; echo -$t -n "-"'n' hello
echo -$t "-n" '-''n' '-n;'         -n hello
export a=l d=s; $a$d
echo $PWD > as ; cat as
echo ''\''"a|"\'q'a'\a'w'
echo \"\|\;\"\| cat -e > \q\w\e\r\t\y ; cat qwerty
pwd >a1>a2>a3; echo s1 >q1 s2>q2 s3; cat a2; cat a3; cat q1; cat q2; 
echo
echo hello '\' ';' "   '\' \" " \" "$PWD\\\"\~\;"\; >> t1 \' \ \ \\
echo hello '\' ';' "   '\' \" " \" "$PWD\\\"\~\;"\; >> t1 \' \ \ \\ ; cat t1
\ls\ ;
echo ${PATH#*:} #Специальная переменная
echo $(( 2#101011 )) #Преобразование системы счисления в арифметической подстановке.

