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

