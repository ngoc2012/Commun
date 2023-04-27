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

make && valgrind --leak-check=full ./minishell
