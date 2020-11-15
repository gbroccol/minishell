#! /bin/bash

# malloc
# is_smb_in_str or if_smb_in_str
#  env // проверить символы по ASCII
# unset VSCODE_GIT_ASKPASS_MAIN SHELL _ Apple_PubSub_Socket_Render PATH SSH_AUTH_SOCK PWD ORIGINAL_XDG_CURRENT_DESKTOP HOME LOGNAME VSCODE_GIT_IPC_HANDLE XPC_FLAGS COLORTERM SHLVL USER
# unset TERM_PROGRAM TMPDIR VSCODE_GIT_ASKPASS_NODE MAKEFLAGS MFLAGS TERM_PROGRAM_VERSION XPC_SERVICE_NAME __CF_USER_TEXT_ENCODING GIT_ASKPASS LANG TERM MAKELEVEL


###############################################################################################
'Hello World!'                                                   # + l
echo 10 > 'abc'"f"                                               # + l
echo 'Hello World!'                                              # + l
echo jbkjnk                                                      # + l
echo abc def                                                     # + l
echo abc             def                                         # +
     echo    890     345                                         # +
ECHO 1223                                                        # +
echo "123" "456"                                                 # +
echo "$"                                                         # +
echo "$/"                                                        # +
echo "$'"                                                        # +
echo "$ "                                                        # +
echo "$$"                                                        # +
echo "\$" '\$' \$                                                # + l
echo "$|$"                                                       # +
echo -n 55                                                       # +
echo -n ''                                                       # +
echo -n 'jbbjhhd'                                                # + l
echo 123 ;                                                       # +
echo 123 ; echo 456                                              # + l
echo "42 ;" ; echo "24 24"                                       # +
echo -n -n -n 23                                                 # + l
echo "\$ \#     |$/\n"                                           # +    
echo "\$|$/"                                                     # +
echo "Это #не комментарий"                                       # +
echo Это # Вот комментарий.                                      # +
echo This              is # comment                              # +
echo Это \# не комментарий                                       # +
echo 567t6 ; 890 -n mk ; echo 123                                # +
echo 567t6 ; 890                                                 # +
echo Это # комментарий                                           # -
echo 123 ; echo Это \# не комментарий                            # + l
# пустая строка                                                  # +
echo $LOGNAME                                                    # + l
echo $LOGNAME\ууу                                                # +
echo $LOGNAME/ууу                                                # +

echo "123 $LOGNAME 456"                                          # +
echo "123 $LOGNAMEeee 456"                                       # +
echo "$LOGNAME/eee"                                              # +

echo '$LOGNAME/eee'                                              # + l
echo '$LOGNAME\eee   |'                                          # +
echo '$PWD'                                                      # +
echo $PWD                                                        # +
echo "$PWD"                                                      # +

echo -n 5 | cat -e                                              # + l
echo 5 | cat -e                                                 # + 
echo "dd" | cat -e                                              # +
echo '||' | cat -e                                              # +
echo 42 23 | grep 4 | cat -e                                    # + l
ls 1111111 | grep 111 | cat -e                                  # +

echo 123 > 1                                                    # + l
echo '123 > 2'                                                  # + l
echo "123 > 1"                                                  # + l
echo > 1                                                        # + l
echo "> 1"                                                      # + l

echo 42 > 2 ; echo 22 >> 2 ; cat -e  2                          # + l
grep 2 < 1                                                      # + l
echo < 1                                                        # + l
grep < 1                                                        # + l
grep 4 < 1 | cat -e                                            	# + l

export qwe=123456 ; echo $qwe                                   # + l

echo "qwe"'qwe'                                                 # + l
echo "qwe" 'qwe'                                                # +

ls                                                              # + l
./ls                                                           	# + l

# bash: syntax error near unexpected token
# start
;;                                                                             # + l 
;                                                                              # + l 
|                                                                              # + l 
||                                                                             # + l 
;@@;                                                                           # + l 
| |                                                                            # + l 
""                                                                             # + l
echo " \'   \\    \$    \`  "                                                  # + l
echo ' \'   \\    \$    \`  ''                                                 # + l
echo \'                                                                        # + l
echo "\'"                                                                      # + l

echo 5 | cat -e                                                                # + l
echo 5 || cat -e                                                               # + l
echo 5 ||| cat -e                                                              # + l

echo 5 |                                                                       # + l
|

ls;;                                                                            # + l
ls; ;                                                                           # + l

ls |                                                                            # + l
ls||                                                                            # + l
ls | |                                                                          # + l

echo $PWD                                                                       # +
echo $321                                                                       # +

echo $\321                                                                      # + l
echo $|                                                                         # +
echo $|cat                                                                      # +
echo $|cat -e                                                                   # +
echo $|321                                                                      # +  
echo $;321                                                                      # +
echo $/321                                                                      # +
echo $'321'                                                                     # +
echo $ 321                                                                      # +
echo $"321"                                                                     # +
echo "$'321"                                                                    # +


export qwe=123456 ; echo $qwe													# + l

echo $fdsgbkldmbklfdsmklfmd                                                     # + l
echo str1"'str2'"                                                               # + l
echo str1"'$str2'"                                                              # +
echo 'str1'str2"str3 $PWD str4" "str5"'$PWD' $PWD "$PWD"                        # + l
echo "hello><; world"                                                           # + l
echo $hfkdghldf$PWD                                                             # +
echo ' """" '                                                                   # +
echo " '''''' "                                                                 # +
echo """"""""                                                                   # + l
echo ''''''''                                                                   # +
echo """"""""""              :""                                                # +
echo """""""""",         wtf     :""                                            # +
echo """""""""",         wtf     :""                                            # +
echo '"""""""""",         wtf     :""'                                          # + l
echo hello                       happy                               man        # +

export = ; echo $?                                                              # + l
export =  ; echo $?                                                             # + l
export =123  ; echo $?                                                          # + l
export 4= ; echo $?                                                             # + l
export 4p=123  ; echo $?                                                        # +
export p=123  ; echo $?                                                         # +
export "s=c";export "$s=s";echo $s $c											# + l
echo $?                                                                         # +
echo '$?'                                                                       # +
echo "$?"                                                                       # +
echo $?$PWD                                                                     # + l
echo $?$.                                                                       # +
echo $.                                                                         # +
echo $?123                                                                      # +
echo "$?123"                                                                    # +
echo $? | cat - e                                                               # + l
echo $? | cat -e                                                                # +
cho $? | cat -e                                                                 # +
echo $? ; ls ; echo $?...                                                       # + l
'e'c"h"o 5                                                                      # + l
'echo' 5                                                                        # +
'ec"h"o' 5                                                                      # +



...$?...                                                                        # + l
echo $? ; ls ; ...$?...                                                         # + l
...$?... ; echo $? ; ls ; ...$?...                                              # + l
export str1 2str = _3str str4=str5   ; echo $?                                  # + l
 'e'"x"p'o'r't'                                                                 # + l
ec"ho" $str1 $str4                                                              # + l 
 'export' 'q'=e "w"=c e="h" r='o' 't'='x' "y"="p" u=r i=t                       # + l
  'e'"x"p'o'r't' "t"$q's'$i='h'"e"'l'l$r                                        # + l
echo "hello;"; $q'c'"h"o $test                                                  # + l
echo "hello;"; $q'c'"h"o $test                                                  # + l
$q$w$e'o' $PWD;   cd .. ;    $q"c"$e'o' $PWD    ;                               # + l
cd -; pwd                                                                       # + l
$lkjlkjllkdfs$q$w$e$r "$e"$q"l"'l'$r;                                           # + l
 echo         \'\"\\                                                            # + l
echo ~                                                                          # + l
echo hello sad man                                                              # + l
echo $?                                                                         # + l
>fil$q'1' e$w"ho" s$i"r"ing f$r$u file1                                         # + l
pwd ; cat file1                                                                 # + l
ls lskdgjdhgisdoigjiredg                                                        # + l
echo $?                                                                         # + l
echo $?                                                                         # + l
unset PWD; echo $PWD                                                            # + l
ls; unset PATH; ls     ;                                                        # + l     КАТЯ скорректировать сообщение об ошибке
echo $?                                                                         # + l
echo $?                                                                         # + l
export PATH=/  ; ls                                                             # + l
echo $?                                                                         # + l
export PATH=/bin  ; ls                                                          # + l
echo $?                                                                         # + l
echo $PWD; unset PWD                                                            # + l
echo $PWD; export PWD=/ ; echo $PWD;                                            # + l
pwd; echo $PWD                                                                  # + l
cd; echo $PWD; cd -                                                             # + l
echo $PWD; echo $OLDPWD                                                         # + l
unset OLDPWD; echo $OLDPWD                                                      # + l
cd; echo $OLDPWD                                                                # + l
cd ; echo $PWD; echo $OLDPWD                                 					# + l
cd -                                                                            # + l
ls -la                                                                          # + l
ls "-la" ; cd -                                                                 # + l
echo '\'                                                                        # + l
echo \hello \$PWD                                                               # + l
echo '\hello \$PWD'                                                             # + l
echo "\hello \$PWD"                                                             # + l
echo \'\"\\ "\hello\$PWD"                                                       # + l
echo "\$PWD" "\PWD"                                                             # + l
echo "\""                                                                       # + l
echo "\'"                                                                       # + l
"echo f" hello                                                                  # + l
>"helo l" echo hell\ f                                                          # + l
>>"helo l" echo hell\ f ; echo hell\ f                                          # + l
export t=n; echo -$t -n "-"'n' hello                                            # + l
export t=n; echo -n "-"'n' hello                                                # + l
echo -n "-"'n' hello                                                            # + l
echo -$t "-n" '-''n' '-n;'         -n hello                                     # + l
export a=l d=s; $a$d                                                            # + l
echo $PWD > as ; cat as                                                         # + l
echo ''\''"a|"\'q'a'\a'w'                                                       # + l
echo \"\|\;\"\| cat -e > \q\w\e\r\t\y ; cat qwerty                              # + l
pwd >a1>a2>a3                                                                   # + l
pwd >a1>a2>a3; echo s1 >q1 s2>q2 s3; cat a2; cat a3; cat q1; cat q2;            # + l 
echo hi >16>17                                                                 	# + l
echo hi > 16 > 17                                                               # + l
echo "hi" ">" "18" '>' '19' > 20                                                # + l
echo "hi" ">" 18 '>' 19 > 20                                                    # + l
echo "hi" ">" 18 > 19 > 20                                                      # + l
echo "hi" > 18 > 19 > 20                                                        # + l



echo 123> 1                                                                     		# - прости меня, КАТЯ НАСТЯ
echo 123jrd> 3                                                                  # + l
echo                                                                            # + l
echo hello '\' ';' "   '\' \" " \" "$PWD\\\"\~\;"\; >> t1 \' \ \ \\             # + l
echo hello '\' ';' "   '\' \" " \" "$PWD\\\"\~\;"\; >> t1 \' \ \ \\ ; cat t1    # + l
\ls\ ;                                                                          # + l
cd
export PWD=/Users/GBroccol
pwd
export HOME=/Users/GBroccol
cd
pwd
echo -n -nnnnn 5                                                                # + l
export N=n                                                                      # + l
echo -n -nnnnn -$N write                                                        # + l
123 ctrl+\abc																	# -
/bin/ls																			# + l
/bin/ls -la 																	# + l
/bin/ls -la ~/school21															# + l
echo $XPC_FLAGS                   -> 0x0                                       	# -
echo $XPC_FLAGS                   -> 0x#0                                       # -
echo $XPC_FLAGS                   -> 0x||0                                      # -
echo nsdjknv -n																	# + l
exit 42																			# + l
echo $?																			# + l
bash
#export написать по алфавиту НАСТЯ

ls > 66 ; ls >>>> 77

ls > 3 | ls > 4 ; ls > 5
ls > a | ls > b 																# - l
ls > a >> b | pwd | cat -e >> b
ls > a > b > c | cat -e < c
ls > a > b | cat -e < b
ls | cat -e < b
pwd | cat -e | cat -e > a >> b | pwd | cat -e >> b
cat -e < a #КАТЯ cat продолжает читать
echo 5 | exit
exit
wc Makefile																		# +
wc < Makefile																	# +

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
cd minishell																		# + l
cd libft																			# + l
cd ..																				# + l
cd .																				# + l
cd ~																				# + l
cd Desktop																			# + l

###############################################################################################
pwd																					# + l
 
###############################################################################################
export																						# - Нужна сортировка

ex $FINAL=5																					# - КАТЯ
env

ex $FINAL=BASH																				# - КАТЯ
env

FINAL=SUN																					# - КАТЯ
export FINAL																				# - КАТЯ
env

final=sun																					# - КАТЯ
export final																				# - КАТЯ
env

###############################################################################################
unset USER42																		# +
unset MAIL42																		# +

###############################################################################################
env																					# +

###############################################################################################
exit																				# +
exit 23																				# +
exit 23 sdfsdf																		# +
exit 23 45 67																		# +
exit sdfsf sdfdsf sdfsdf															# +
exit sdfsf 123																		# +						
###############################################################################################
/bin/ls																				# +
/bin/echo 12																		# +
ls -la																				# +
/bin/ls																				# +
echo $?																				# +
/bin/ls ffffff																		# +
echo $?																				# +
/bin/ls ; echo -n 42;echo 42														# +
cat																					# +
unset PATH																			# +
ls																							# - КАТЯ скорректировать сообщение об ошибке
export PATH=/bin																	# +
ls																					# +

#################################################################################
