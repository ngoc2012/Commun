# MINISHELL-TESTER

RESET="\033[0m"
BLACK="\033[30m"
RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
BLUE="\033[34m"
MAGENTA="\033[35m"
CYAN="\033[36m"
WHITE="\033[37m"

BOLDBLACK="\033[1m\033[30m"
BOLDRED="\033[1m\033[31m"
BOLDGREEN="\033[1m\033[32m"
BOLDYELLOW="\033[1m\033[33m"
BOLDBLUE="\033[1m\033[34m"
BOLDMAGENTA="\033[1m\033[35m"
BOLDCYAN="\033[1m\033[36m"
BOLDWHITE="\033[1m\033[37m"

# Compile and set executable rights
make -C ../ > /dev/null
cp ../minishell .
chmod 755 minishell

function exec_test()
{
	TEST1=$(echo $@ "; exit" | ./minishell 2>&-)
	ES_1=$?
	TEST2=$(echo $@ "; exit" | bash 2>&-)
	ES_2=$?
	if [ "$TEST1" == "$TEST2" ] && [ "$ES_1" == "$ES_2" ]; then
		printf " $BOLDGREEN%s$RESET" "✓ "
	else
		printf " $BOLDRED%s$RESET" "✗ "
	fi
	printf "$CYAN \"$@\" $RESET"
	if [ "$TEST1" != "$TEST2" ]; then
		echo
		echo
		printf $BOLDRED"Your output : \n%.20s\n$BOLDRED$TEST1\n%.20s$RESET\n" "-----------------------------------------" "-----------------------------------------"
		printf $BOLDGREEN"Expected output : \n%.20s\n$BOLDGREEN$TEST2\n%.20s$RESET\n" "-----------------------------------------" "-----------------------------------------"
	fi
	if [ "$ES_1" != "$ES_2" ]; then
		echo
		echo
		printf $BOLDRED"Your exit status : $BOLDRED$ES_1$RESET\n"
		printf $BOLDGREEN"Expected exit status : $BOLDGREEN$ES_2$RESET\n"
	fi
	echo
	sleep 0.1
}

printf "$BOLDMAGENTA __  __ _____ _   _ _____  _____ _    _ ______ _      _      \n"
printf "|  \/  |_   _| \ | |_   _|/ ____| |  | |  ____| |    | |     \n"
printf "| \  / | | | |  \| | | | | (___ | |__| | |__  | |    | |     \n"
printf "| |\/| | | | | . \` | | |  \___ \|  __  |  __| | |    | |     \n"
printf "| |  | |_| |_| |\  |_| |_ ____) | |  | | |____| |____| |____ \n"
printf "|_|  |_|_____|_| \_|_____|_____/|_|  |_|______|______|______|\n$RESET"
echo


#exec_test "    \(echo a && \(echo \"asidj\"; || echo a\"sddfsd\"  \)  \)  "
#exec_test " (echo 1   &&  echo 2 ||  ( (  echo 3 || echo  4  && echo 5 )  && echo 6 ) && echo 7 ) "
#exec_test "echo 0 && (echo 1 && (echo 11 && (echo 12 && echo 13))  &&  echo 2 ||  ( (  echo 3 || echo  4  && echo 5 )  && echo 6 ) && echo 7 )"
#exec_test "(echo a && > echo b || > echo c)"
#exec_test "((echo echo) && cd)"
#exec_test "(cd sdfsdg && echo a) echo b"
#exec_test "(cd sdfsdg && echo a) && echo b"
#exec_test "("
#exec_test ")"
#exec_test ")("
#exec_test "()"
# ECHO TESTS
exec_test 'echo test tout'
exec_test 'echo test      tout'
exec_test 'echo -n test tout'
exec_test 'echo -n -n -n test tout'


# CD TESTS
exec_test 'cd .. ; pwd'
exec_test 'cd /Users ; pwd'
exec_test 'cd ; pwd'
exec_test 'mkdir test_dir ; cd test_dir ; rm -rf ../test_dir ; cd . ; pwd ; cd . ; pwd ; cd .. ; pwd'


# PIPE TESTS
exec_test 'cat tests/lorem.txt | grep arcu | cat -e'
exec_test 'echo test | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e| cat -e| cat -e| cat -e| cat -e| cat -e| cat -e| cat -e| cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e'
#exec_test 'cat /dev/random | head -c 100 | wc -c'
exec_test 'ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls'
exec_test 'ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls'

# ENV EXPANSIONS + ESCAPE
exec_test 'echo test     \    test'
exec_test 'echo \"test'
exec_test 'echo $TEST'
exec_test 'echo "$TEST"'
exec_test "echo '$TEST'"
exec_test 'echo "$TEST$TEST$TEST"'
exec_test 'echo "$TEST$TEST=lol$TEST"'
exec_test 'echo "   $TEST lol $TEST"'
exec_test 'echo $TEST$TEST$TEST'
exec_test 'echo $TEST$TEST=lol$TEST""lol'
exec_test 'echo    $TEST lol $TEST'
exec_test 'echo test "" test "" test'
exec_test 'echo "\$TEST"'
exec_test 'echo "$=TEST"'
exec_test 'echo "$"'
exec_test 'echo "$?TEST"'
exec_test 'echo $TEST $TEST'
exec_test 'echo "$1TEST"'
exec_test 'echo "$T1TEST"'

# ENV EXPANSIONS
ENV_SHOW="env | sort | grep -v SHLVL | grep -v _="
EXPORT_SHOW="export | sort | grep -v SHLVL | grep -v _= | grep -v OLDPWD"
exec_test 'export ='
exec_test 'export 1TEST= ;' $ENV_SHOW
exec_test 'export TEST ;' $EXPORT_SHOW
exec_test 'export ""="" ; ' $ENV_SHOW
exec_test 'export TES=T="" ;' $ENV_SHOW
exec_test 'export TE+S=T="" ;' $ENV_SHOW
exec_test 'export TEST=LOL ; echo $TEST ;' $ENV_SHOW
exec_test 'export TEST=LOL ; echo $TEST$TEST$TEST=lol$TEST'
exec_test 'export TEST=LOL; export TEST+=LOL ; echo $TEST ;' $ENV_SHOW
exec_test $ENV_SHOW
exec_test $EXPORT_SHOW
exec_test 'export TEST="ls       -l     - a" ; echo $TEST ; $LS ; ' $ENV_SHOW

# REDIRECTIONS
exec_test 'echo test > ls ; cat ls'
exec_test 'echo test > ls >> ls >> ls ; echo test >> ls; cat ls'
exec_test '> lol echo test lol; cat lol'
exec_test '>lol echo > test>lol>test>>lol>test mdr >lol test >test; cat test'
exec_test 'cat < ls'
exec_test 'cat < ls > ls'

# MULTI TESTS
exec_test 'echo testing multi ; echo "test 1 ; | and 2" ; cat tests/lorem.txt | grep Lorem'

# SYNTAX ERROR
exec_test ';; test'
exec_test '| test'
exec_test 'echo > <'
exec_test 'echo | |'
exec_test '<'

# EXIT
exec_test "exit 42"
exec_test "exit 42 53 68"
exec_test "exit 259"
exec_test "exit 9223372036854775807"
exec_test "exit -9223372036854775808"
exec_test "exit 9223372036854775808"
exec_test "exit -9223372036854775810"
exec_test "exit -4"
exec_test "exit wrong"
exec_test "exit wrong_command"
exec_test "gdagadgag"
exec_test "ls -Z"
exec_test "cd gdhahahad"
exec_test "ls -la | wtf"



exec_test "echo hello world"
exec_test 'echo "hello world"'
exec_test "echo 'hello world'"
exec_test "echo hello'world'"
exec_test 'echo hello""world'
exec_test "echo ''"
exec_test "echo \"\$PWD\""
exec_test "echo \'\$PWD\'"
exec_test "echo \"aspas ->\'\""
exec_test "echo \"aspas -> \' \""
exec_test "echo \'aspas ->\"\'"
exec_test "echo \'aspas -> \" \'"
exec_test "echo \"> >> < * ? [ ] | ; [ ] || && ( ) & # \$ \ <<\""
exec_test "echo \'\"> >> < * ? [ ] | ; [ ] || && ( ) & # \$ \ <<\"\'"
exec_test "echo \"exit_code ->\$? user ->\$USER home -> \$HOME\""
exec_test "echo 'exit_code ->\$? user ->\$USER home -> \$HOME'"
exec_test "echo \"\$"
exec_test "echo \'\$\'"
exec_test "echo \$"
exec_test "echo \$?"
exec_test "echo \$?HELLO"
exec_test "pwd"
exec_test "pwd oi"
exec_test "export hello"
exec_test "export HELLO=123"
exec_test "export HELLO =123"
exec_test "export HELLO= 123"
exec_test "export A-"
exec_test "export HELLO=123 A"
exec_test "export HELLO=\"123 A-\""
exec_test "export hello world"
exec_test "export HELLO-=123"
exec_test "export ="
exec_test "export 123"
exec_test "unset"
exec_test "unset HELLO"
exec_test "unset HELLO1 HELLO2"
exec_test "unset HOME"
exec_test "unset PATH"
exec_test "unset SHELL"
exec_test "cd \$PWD"
exec_test "cd \$PWD hi "
exec_test "cd 123123"
exec_test "exit 123"
exec_test "exit 298"
exec_test "exit +100"
exec_test "exit \"+100\""
exec_test "exit +\"100\""
exec_test "exit -100"
exec_test "exit \"-100\""
exec_test "exit -\"100\""
exec_test "exit hello"
exec_test "exit 42 world"
exec_test "exit 9223372036854775807"
exec_test "exit 9223372036854775808"
exec_test "exit -9223372036854775807"
exec_test "exit -9223372036854775808"
exec_test "exit -9223372036854775809"


exec_test "ls >outfile01 && cat outfile01"
#exec_test "cat <minishell.h&ls"
exec_test "||"
exec_test "|| echo oi"
exec_test "&"
exec_test "&&"
exec_test "|& #-> não precisa"
exec_test "*"
#exec_test "> *"
#exec_test ">> *"
exec_test "> & # valido para < e >>"
#exec_test "> &&"
#exec_test "> ||"
exec_test "echo oi || echo tchau"
exec_test "env | grep USER || grep lucas"
#exec_test "> *"
#exec_test ">> *"
#exec_test "< *"
#exec_test "<< *"


exec_test "env | sort | grep -v SHLVL | grep -v ^_"
exec_test "export | sort | grep -v SHLVL | grep -v \"declare -x _\" | grep -v \"PS.=\""
exec_test "cat ./test_files/infile_big | grep oi"
exec_test "cat minishell.h | grep \");\"\$"
exec_test "export GHOST=123 | env | grep GHOST"
exec_test "grep hi <./test_files/infile"
exec_test "grep hi \"<infile\" <         ./test_files/infile"
exec_test "echo hi < ./test_files/infile bye bye"
exec_test "grep hi <./test_files/infile_big <./test_files/infile"
exec_test "echo <\"./test_files/infile\" \"bonjour       42\""
exec_test "cat <\"./test_files/file name with spaces\""
exec_test "cat <./test_files/infile_big ./test_files/infile"
exec_test "cat <\"1\"\"2\"\"3\"\"4\"\"5\""
exec_test "echo <\"./test_files/infile\" <missing <\"./test_files/infile\""
exec_test "echo <missing <\"./test_files/infile\" <missing"
exec_test "cat <\"./test_files/infile\""
exec_test "echo <\"./test_files/infile_big\" | cat <\"./test_files/infile\""
exec_test "echo <\"./test_files/infile_big\" | cat \"./test_files/infile\""
exec_test "echo <\"./test_files/infile_big\" | echo <\"./test_files/infile\""
exec_test "echo hi | cat <\"./test_files/infile\""
exec_test "echo hi | cat \"./test_files/infile\""
exec_test "cat <\"./test_files/infile\" | echo hi"
exec_test "cat <\"./test_files/infile\" | grep hello"
exec_test "cat <\"./test_files/infile_big\" | echo hi"
exec_test "cat <missing"
exec_test "cat <missing | cat"
exec_test "cat <missing | echo oi"
exec_test "cat <missing | cat <\"./test_files/infile\""
exec_test "echo <123 <456 hi | echo 42"
exec_test "ls >./outfiles/outfile01"
exec_test "ls >         ./outfiles/outfile01"
exec_test "echo hi >         ./outfiles/outfile01 bye"
exec_test "ls >./outfiles/outfile01 >./outfiles/outfile02"
exec_test "ls >./outfiles/outfile01 >./test_files/invalid_permission"
exec_test "ls >\"./outfiles/outfile with spaces\""
exec_test "ls >\"./outfiles/outfile\"\"1\"\"2\"\"3\"\"4\"\"5\""
exec_test "ls >\"./outfiles/outfile01\" >./test_files/invalid_permission >\"./outfiles/outfile02\""
exec_test "ls >./test_files/invalid_permission >\"./outfiles/outfile01\" >./test_files/invalid_permission"
exec_test "cat <\"./test_files/infile\" >\"./outfiles/outfile01\""
exec_test "echo hi >./outfiles/outfile01 | echo bye"
exec_test "echo hi >./outfiles/outfile01 >./outfiles/outfile02 | echo bye"
exec_test "echo hi | echo >./outfiles/outfile01 bye"
exec_test "echo hi | echo bye >./outfiles/outfile01 >./outfiles/outfile02"
exec_test "echo hi >./outfiles/outfile01 | echo bye >./outfiles/outfile02"
exec_test "echo hi >./outfiles/outfile01 >./test_files/invalid_permission | echo bye"
exec_test "echo hi >./test_files/invalid_permission | echo bye"
exec_test "echo hi >./test_files/invalid_permission >./outfiles/outfile01 | echo bye"
exec_test "echo hi | echo bye >./test_files/invalid_permission"
exec_test "echo hi | >./outfiles/outfile01 echo bye >./test_files/invalid_permission"
exec_test "echo hi | echo bye >./test_files/invalid_permission >./outfiles/outfile01"
exec_test "cat <\"./test_files/infile\" >./test_files/invalid_permission"
exec_test "cat >./test_files/invalid_permission <\"./test_files/infile\""
exec_test "cat <missing >./outfiles/outfile01"
exec_test "cat >./outfiles/outfile01 <missing"
exec_test "cat <missing >./test_files/invalid_permission"
exec_test "cat >./test_files/invalid_permission <missing"
exec_test "cat >./outfiles/outfile01 <missing >./test_files/invalid_permission"
exec_test "ls >>./outfiles/outfile01"
exec_test "ls >>      ./outfiles/outfile01"
exec_test "ls >>./outfiles/outfile01 >./outfiles/outfile01"
exec_test "ls >./outfiles/outfile01 >>./outfiles/outfile01"
exec_test "ls >./outfiles/outfile01 >>./outfiles/outfile01 >./outfiles/outfile02"
exec_test "ls >>./outfiles/outfile01 >>./outfiles/outfile02"
exec_test "ls >>./test_files/invalid_permission"
exec_test "ls >>./test_files/invalid_permission >>./outfiles/outfile01"
exec_test "ls >>./outfiles/outfile01 >>./test_files/invalid_permission"
exec_test "ls >./outfiles/outfile01 >>./test_files/invalid_permission >>./outfiles/outfile02"
exec_test "ls <missing >>./test_files/invalid_permission >>./outfiles/outfile02"
exec_test "ls >>./test_files/invalid_permission >>./outfiles/outfile02 <missing"
exec_test "echo hi >>./outfiles/outfile01 | echo bye"
exec_test "echo hi >>./outfiles/outfile01 >>./outfiles/outfile02 | echo bye"
exec_test "echo hi | echo >>./outfiles/outfile01 bye"
exec_test "echo hi | echo bye >>./outfiles/outfile01 >>./outfiles/outfile02"
exec_test "echo hi >>./outfiles/outfile01 | echo bye >>./outfiles/outfile02"
exec_test "echo hi >>./test_files/invalid_permission | echo bye"
exec_test "echo hi >>./test_files/invalid_permission >./outfiles/outfile01 | echo bye"
exec_test "echo hi | echo bye >>./test_files/invalid_permission"
exec_test "echo hi | echo >>./outfiles/outfile01 bye >./test_files/invalid_permission"
exec_test "cat <minishell.h>./outfiles/outfile"
exec_test "cat <minishell.h|ls"
exec_test "|"
exec_test "| echo oi"
exec_test "| |"
exec_test "| $"
exec_test "| >"
exec_test ">"
exec_test ">>"
exec_test ">>>"
exec_test "<"
exec_test "<<"
exec_test "echo hi <"
exec_test "cat    <| ls"
exec_test "echo hi | >"
exec_test "echo hi | > >>"
exec_test "echo hi | < |"
exec_test "echo hi |   |"
exec_test "echo hi |  \"|\""
exec_test "echo *.md"
exec_test "echo built*"
exec_test "echo oi*"
exec_test "echo *.supp"
exec_test "echo 'bye *' bo*s bye"
exec_test "echo 'bye *' mini* bye"
exec_test "echo *ME*"
exec_test "echo \"*\""
exec_test "\"*\""
exec_test "manual*"
#exec_test "echo * | awk -v RS=\" \" '{print}' | sort"
exec_test "<*.txt"
exec_test "echo 'bye *' t*.c bye"
exec_test "echo *EMPTY hello READ* world"
exec_test "cat <README*"
exec_test "echo \"pip*\""
exec_test "echo *bonus *.supp bonjour"
exec_test "\"ls test\"*"
exec_test "export a=\"port\"; ex\$a b=\"export\"; echo \$b; \"\$b\" c=\"export\"; echo \$c"
exec_test "\"export\" d=\"exp\"; echo \$d; \$d\"ort\" e=\"xpor\"; echo \$e; e\"\$e\"t f=\"no\"; echo \$f"
exec_test "echo c=\"s *\""
exec_test "export a=\"s *\"; echo \$a; echo \"\$a\"; l\"\$a\""
exec_test "echo \"ngoc\"\"ngoc\""
exec_test "echo \'\"ngoc\" \"ngoc\"\'"
exec_test "echo \'\"ngoc\'\" \"\'ngoc\"\'"
exec_test "echo \"\$USERRRR\""
exec_test "echo \"\$USER\""
exec_test "echo \"\$USERa\""
exec_test "echo \"a \$USER a\""
exec_test "echo \"a\$USER a\""
exec_test "echo \"a\$USERa\" a"
exec_test "echo \"ab\"\"a\$USERa\" a"
exec_test "echo \"ab\"\"a\$USER\" a"
exec_test "echo \"ab\"\"a\$USER b\" a"
exec_test "echo \"ab\"\'a\$USER b\' a"
exec_test "echo \"ab\"\"\'a\$USER b\'\" a"
exec_test "echo \"\$USERRRRa\""


rm lol ls test
