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

