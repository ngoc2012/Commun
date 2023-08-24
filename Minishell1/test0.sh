export | sort | grep -v SHLVL | grep -v "declare -x _" | grep -v "PS.="


ngoc@ngoc-HP-EliteBook-850-G5:~/Commun/Minishell/minishell-tester$ export | grep USER
declare -x USER="ngoc"
declare -x USERNAME="ngoc"
ngoc@ngoc-HP-EliteBook-850-G5:~/Commun/Minishell/minishell-tester$ export A=b | export C=a | grep A
ngoc@ngoc-HP-EliteBook-850-G5:~/Commun/Minishell/minishell-tester$ echo $A

ngoc@ngoc-HP-EliteBook-850-G5:~/Commun/Minishell/minishell-tester$ echo $C

ngoc@ngoc-HP-EliteBook-850-G5:~/Commun/Minishell/minishell-tester$ 


echo "\$TEST"
echo testing multi ; echo "test 1 ; | and 2" ; cat tests/lorem.txt | grep Lorem
echo "ngoc""ngoc"
echo '"ngoc" "ngoc"'
echo '"ngoc'" "'ngoc"'
echo "$USERRRR"
echo "$USER"
echo "$USERa"
echo "a $USER a"
echo "a$USER a"
echo "a$USERa" a
echo "ab""a$USERa" a
echo "ab""a$USER" a
echo "ab""a$USER b" a
echo "ab"'a$USER b' a
echo "ab""'a$USER b'" a
echo "$USERRRRa"
echo a"
echo $\$A
$USER
"
echo  a     a   a
echo    a    "a"   a
echo   a    'a'
echo   a"a"'a'
echo   -n
echo   -n  a"a'"
echo "/home/$USER/Commun"
echo "/home/$USER$Commun"
echo "$USERa"
echo "$USER+a"
echo "$USER$+a"
echo "$USERa+++"

cd / && cd ../../
ls "/home/$USER""/Commun/Minishell/tes t/test$" /home/$USER
Error:
echo a; echo b; && echo c;
OK:
echo a; echo b && echo c;
    (echo a && (echo "asidj"; || echo a'sddfsd'  )  )  
   (echo 1   &&  echo 2 ||  ( (  echo 3 || echo  4  && echo 5 )  && echo 6 ) && echo 7 )     
echo 0 && (echo 1 && (echo 11 && (echo 12 && echo 13))  &&  echo 2 ||  ( (  echo 3 || echo  4  && echo 5 )  && echo 6 ) && echo 7 )
echo *es*s*



ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ (echo a
> 
> 
>   && echo b)
bash: syntax error near unexpected token `&&'
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ (echo a
> 
> ) && echo b
a
b
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ (echo a
> 
> 
> ;)
bash: syntax error near unexpected token `;'
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ (echo a;
> 
> 
> 
> )
a
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ (echo a; )
a
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ (echo a;
> 
> 
> echo b) && echo c
a
b
c
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ (echo a
>
>
> ) && echo b
a
b
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ (echo a
>
>
> echo b) && echo c
a
b
c
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ (echo a
> echo b
> echo c
> ) && echo d
a
b
c
d
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ (echo a
> echo b) echo c
bash: syntax error near unexpected token `echo'
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ ((echo a
> echo b)
> echo c && echo d)
a
b
c: command not found
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ ((echo a
> echo b)
> echo)
a
b
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ ((echo a
> echo b)
> )
a
b
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ ((echo a
> echo b))
bash: ((: echo a
echo b: syntax error in expression (error token is "a
echo b")
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ (echo a
> echo b)
a
b
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ ((echo a))
bash: ((: echo a: syntax error in expression (error token is "a")
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ ((echo echo))
bash: ((: echo echo: syntax error in expression (error token is "echo")
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ (   (echo echo)  )
echo
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ ( (echo echo) )
echo
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ ( (echo echo))
echo
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ ((echo echo) )
echo
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ ((echo echo)echo)
bash: syntax error near unexpected token `echo'
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ ((echo echo)cd)
bash: syntax error near unexpected token `cd'
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ ((echo echo) && cd)
echo
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ ((echo echo) && echo a)
echo
a
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ cd
ngoc@ngoc-ThinkPad-W530:~$ cd Commun/Minishell/
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ ((echo echo) && echo b)
echo
b
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ (echo a &&
> echo b ||
> echo c
> ;
bash: syntax error near unexpected token `;'
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ (echo a &&
> echo b ||
> echo c)
a
b
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ (echo a &&
> echo b) ||
> echo c
a
b
ngoc@ngoc-ThinkPad-W530:~$ > lol echo > test "haha"
ngoc@ngoc-ThinkPad-W530:~$ cat test
haha
ngoc@ngoc-ThinkPad-W530:~$ > lol > test echo "haha"
ngoc@ngoc-ThinkPad-W530:~$ cat test
haha
ngoc@ngoc-ThinkPad-W530:~$ > lol echo "hehe" > test
ngoc@ngoc-ThinkPad-W530:~$ cat test
hehe
ngoc@ngoc-ThinkPad-W530:~$ > lol echo "hehe" echo "haha"> test
ngoc@ngoc-ThinkPad-W530:~$ cat test
hehe echo haha
goc@ngoc-ThinkPad-W530:~$ cat lol
ngoc@ngoc-ThinkPad-W530:~$ > lol echo "hehe" > test echo haha > ls
ngoc@ngoc-ThinkPad-W530:~$ cat ls
hehe echo haha
ngoc@ngoc-ThinkPad-W530:~$ cat test
ngoc@ngoc-ThinkPad-W530:~$ > lol cd Documents > test echo haha > ls
bash: cd: too many arguments
ngoc@ngoc-ThinkPad-W530:~$   >   < test
bash: syntax error near unexpected token `<'
ngoc@ngoc-ThinkPad-W530:~$  < 
bash: syntax error near unexpected token `newline'
ngoc@ngoc-ThinkPad-W530:~$ < >
bash: syntax error near unexpected token `>'



ngoc@ngoc-ThinkPad-W530:~$ echo a; > lol > dsff echo b > test
a
ngoc@ngoc-ThinkPad-W530:~$ cat test
b
ngoc@ngoc-ThinkPad-W530:~$ cat lol
ngoc@ngoc-ThinkPad-W530:~$ cat dsff
ngoc@ngoc-ThinkPad-W530:~$ cat < test < test
b
ngoc@ngoc-ThinkPad-W530:~$ cat < tests < test
bash: tests: No such file or directory
ngoc@ngoc-ThinkPad-W530:~$ cat < test < lol < dsff < test
b
ngoc@ngoc-ThinkPad-W530:~$ cat > alo < test < lol < dsff < test
ngoc@ngoc-ThinkPad-W530:~$ cat alo
b
ngoc@ngoc-ThinkPad-W530:~$ cat < test < lol < dsff < test > alo1 > alo
ngoc@ngoc-ThinkPad-W530:~$ cat alo
b



ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ echo 1 && echo 2 || cd dsfsdf || echo 4
1
2
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ echo 1 && echo 2 || cd dsfsdf && echo 4
1
2
4
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ echo 1 && cd hsadf || cd dsfsdf && echo 4
1
bash: cd: hsadf: No such file or directory
bash: cd: dsfsdf: No such file or directory
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ echo 1 && cd hsadf || echo 3 && echo 4
1
bash: cd: hsadf: No such file or directory
3
4
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ export a='s *'
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ echo $a
s ft_printf includes input libft ls Makefile man minishell minishell-tester minishell_tester output.txt rl.supp srcs tes t test0.sh test.sh


ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ export a="s *"
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ echo $a
s ft_printf includes input libft ls Makefile man minishell minishell-tester minishell_tester output.txt rl.supp srcs tes t test0.sh test.sh

ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ echo sadfsadf > 'ech*'
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ ls
'$USER'      includes   ls         minishell          ngoc         srcs       test.sh
'ech*'       input      Makefile   minishell-tester   output.txt  'tes t'
 ft_printf   libft      man        minishell_tester   rl.supp      test0.sh
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ cat 'ech*'
sadfsadf
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ echo fsdgsg > "ech*"
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ ls
'$USER'      includes   ls         minishell          ngoc         srcs       test.sh
'ech*'       input      Makefile   minishell-tester   output.txt  'tes t'
 ft_printf   libft      man        minishell_tester   rl.supp      test0.sh
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ cat 'ech*'
fsdgsg
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$

ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ ls 'mini*'
ls: cannot access 'mini*': No such file or directory
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ ls "mini*"
ls: cannot access 'mini*': No such file or directory

ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ echo sadfsadf > '$USER'
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ ls
'$USER'      includes   ls         minishell          output.txt  'tes t'
 echo        input      Makefile   minishell-tester   rl.supp      test0.sh
 ft_printf   libft      man        minishell_tester   srcs         test.sh
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ echo sadfsadf > "$USER"
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ ls
'$USER'      includes   ls         minishell          ngoc         srcs       test.sh
 echo        input      Makefile   minishell-tester   output.txt  'tes t'
 ft_printf   libft      man        minishell_tester   rl.supp      test0.sh



ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ export a='port'
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ ex$a b='export'
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ echo $b
export
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ "$b" c="export"
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ echo $c
export
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ '$b' c="export"
$b: command not found
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ "export" d="exp"
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ echo $d
exp
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ $d"ort" e="xpor"
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ echo $e
xpor
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ e"$e"t f="no"
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ echo $f
no

ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ "ls mini"*
ls mini*: command not found
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ echo c="s *"
c=s *

ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ echo $a
s $USER ech* ft_printf includes input libft ls Makefile man minishell minishell-tester minishell_tester ngoc output.txt rl.supp srcs tes t test0.sh test.sh
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ echo "$a"
s *

ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ l"$a"
ls *: command not found

ngoc@ngoc-HP-EliteBook-850-G5:~/Commun/Minishell$ export a=10 | wc
      0       0       0
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ echo $a

ngoc@ngoc-HP-EliteBook-850-G5:~/Commun/Minishell$ bash
ngoc@ngoc-HP-EliteBook-850-G5:~/Commun/Minishell$ export a=10 | wc
      0       0       0
ngoc@ngoc-HP-EliteBook-850-G5:~/Commun/Minishell$ cd | wc
      0       0       0
ngoc@ngoc-HP-EliteBook-850-G5:~/Commun/Minishell$ pwd | wc
      1       1      28
ngoc@ngoc-HP-EliteBook-850-G5:~/Commun/Minishell$ pwd | wc | exit
ngoc@ngoc-HP-EliteBook-850-G5:~/Commun/Minishell$

ngoc@ngoc-HP-EliteBook-850-G5:~/Commun/Minishell$ exit | wc
      0       0       0
ngoc@ngoc-HP-EliteBook-850-G5:~/Commun/Minishell$

ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ echo a | echo b | cat
b

ngoc@ngoc-HP-EliteBook-850-G5:~/Commun/Minishell$ cat << a << b << c
> a
> b
> sdaffsad
> c
sdaffsad

ngoc@ngoc-HP-EliteBook-850-G5:~/Commun/Minishell$ cat << << a
bash: syntax error near unexpected token `<<'
ngoc@ngoc-HP-EliteBook-850-G5:~/Commun/Minishell$ cat << < a
bash: syntax error near unexpected token `<'
ngoc@ngoc-HP-EliteBook-850-G5:~/Commun/Minishell$ cat << |
bash: syntax error near unexpected token `|'
ngoc@ngoc-HP-EliteBook-850-G5:~/Commun/Minishell$ cat << > a
bash: syntax error near unexpected token `>'
ngoc@ngoc-HP-EliteBook-850-G5:~/Commun/Minishell$ cat << >> a
bash: syntax error near unexpected token `>>'
ngoc@ngoc-HP-EliteBook-850-G5:~/Commun/Minishell$ vi test0.sh
ngoc@ngoc-HP-EliteBook-850-G5:~/Commun/Minishell$ cat <<>
bash: syntax error near unexpected token `>'
ngoc@ngoc-HP-EliteBook-850-G5:~/Commun/Minishell$ cat <<>>
bash: syntax error near unexpected token `>>'
ngoc@ngoc-HP-EliteBook-850-G5:~/Commun/Minishell$ cat <<>>sdfsdf
bash: syntax error near unexpected token `>>'
ngoc@ngoc-HP-EliteBook-850-G5:~/Commun/Minishell$ cat <<>>>sdfsdf
bash: syntax error near unexpected token `>>'


ngoc@ngoc-HP-EliteBook-850-G5:~/Commun/Minishell$ cat << a < c
> hehe
> a
total 304
drwxrwxr-x  8 ngoc ngoc  4096 juin   8 11:07 .
drwxr-xr-x 21 ngoc ngoc  4096 mai   20 20:22 ..
-rw-rw-r--  1 ngoc ngoc     0 juin   8 11:10 a
-rw-rw-r--  1 ngoc ngoc     0 juin   8 11:10 b
-rw-rw-r--  1 ngoc ngoc     0 juin   8 11:13 c
-rw-rw-r--  1 ngoc ngoc     4 mai   31 13:06 echo
drwxrwxr-x  2 ngoc ngoc  4096 juin   8 09:01 ft_printf
-rw-rw-r--  1 ngoc ngoc    10 juin   8 09:59 hehe
drwxrwxr-x  2 ngoc ngoc  4096 juin   8 10:28 includes
-rw-rw-r--  1 ngoc ngoc    32 mai   13 17:51 input
drwxrwxr-x  2 ngoc ngoc  4096 juin   8 09:01 libft
-rwxrwxr-x  1 ngoc ngoc 57496 mai   11 11:24 ls
-rw-rw-r--  1 ngoc ngoc  1961 mai   31 13:06 Makefile
-rw-rw-r--  1 ngoc ngoc 49239 mai    3 18:58 man
-rwxrwxr-x  1 ngoc ngoc 78168 juin   8 11:07 minishell
drwxrwxr-x  2 ngoc ngoc  4096 mai    3 18:58 minishell-tester
drwxrwxr-x  4 ngoc ngoc  4096 mai    3 18:58 minishell_tester
-rw-rw-r--  1 ngoc ngoc     9 mai   16 19:36 ngoc
-rw-rw-r--  1 ngoc ngoc    18 mai   13 17:51 output.txt
-rw-rw-r--  1 ngoc ngoc    82 mai   16 19:36 rl.supp
drwxrwxr-x  3 ngoc ngoc  4096 juin   8 11:07 srcs
-rw-rw-r--  1 ngoc ngoc    11 juin   8 10:44 stdout.out
-rwxrwxr-x  1 ngoc ngoc 18544 juin   8 10:44 test
-rw-rw-r--  1 ngoc ngoc  9879 mai   31 13:06 test0.sh
-rw-rw-r--  1 ngoc ngoc   782 juin   8 10:44 test.c
-rw-rw-r--  1 ngoc ngoc  6544 juin   7 09:14 test.o
-rw-rw-r--  1 ngoc ngoc   311 mai   31 13:06 test.sh
a
ngoc@ngoc-HP-EliteBook-850-G5:~/Commun/Minishell$ cat < c << a
> hehe
> a
hehe
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ "echo abc \ abc"
echo abc \ abc: command not found
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ echo \" ''
"
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ echo \" 'a'
" a
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ echo "\'"
\'
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ echo \ 
 
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ echo \
>  

ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ echo \ a
 a
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ echo '\ a'
\ a
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ echo "\ a"
\ a
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ bash
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ echo "\ a"
\ a
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ echo "\\ a"
\ a
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ echo "\$? a"
$? a
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ echo "\a"
\a
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ echo '\$? a'
\$? a
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ echo "\1"
\1
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ echo "\-"
\-
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ echo \\ a
\ a
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ echo "\" "a"
> a
> ^C
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ echo a \ a
a  a
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ echo "\ " "a"
\  a
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ eho \" "
>  
> sadf
> ^C
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ echo \" "
> sadsa
>  
> ^C
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ echo \n
n
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ echo "\n"
\n
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ echo '\n'
\n
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ echo \'
'
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ echo "\'"
\'
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ echo '\''
> '
\

ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ echo "'"
'
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ echo a\na
ana
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ echo a \n a
a n a
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ echo -e "\n"


ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ echo "\""
"
ngoc@ngoc-ThinkPad-W530:~/Commun/Minishell$ echo \\
\

