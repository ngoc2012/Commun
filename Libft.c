#include <limits.h>
#include <stdio.h>
#include "Libft/libft.h"
#include "Libs/libft.h"
#include <ctype.h>
#include <string.h>
#include <bsd/string.h>
#include <stdlib.h>

void	test1(unsigned int i, char *s) { s[i] = ft_toupper(s[i]); }
void	test2(unsigned int i, char *s) { s[i] = ft_tolower(s[i]); }
char	test3(unsigned int i, char s) 
{ 
	if (i % 2 == 0)
		return (ft_toupper(s)); 
	else
		return (s);
}

char	test4(unsigned int i, char s)
{
	if (i % 2 == 0)
		return (ft_tolower(s)); 
	else
		return (s);
}

void	test5(void *s) { ft_striteri(s, test1); }
void	test6(void *s) { ft_striteri(s, test2); }
void	*test7(void *s) { return ((void *) ft_strmapi((char*) s, test3)); }
void	*test8(void *s) { return ((void *) ft_strmapi((char*) s, test4)); }

void	print_str(void *s)
{
	if (s) {
		printf("%s\n", (char *) s);
		ft_print_memory(s, 32);
		free(s);
	}
	else
		printf("string NULL\n");
}

void	ft_list_print(t_list *lst)
{
	int	i;
	int	len;

	i = 0;
	len = ft_lstsize(lst);
	while (lst)
	{
		if (lst->content)
		{
			if (i == 0)
				printf("[%s, ", (char *) lst->content);
			else if (i == len - 1)
				printf("%s]", (char *) lst->content);
			else
				printf("%s, ", (char *) lst->content);
		}
		lst = lst->next;
		i++;
	}
	printf("\n");
}

t_list	*ft_list_push_strs(char **strs)
{
	t_list	*begin;
	t_list	*prev;
	t_list	*new;

	begin = 0;
	while (*strs)
	{
		new = ft_lstnew(*strs);
		if (begin)
			prev->next = new;
		else
			begin = new;
		prev = new;
		strs++;
	}
	return (begin);
}

void	ft_free(void *content)
{
	free(content);
}

int	main()
{
	
	printf("========\n");
	printf("isalpha\n");
	printf("%d %d\n", isalpha(1), ft_isalpha(1));
	printf("%d %d\n", isalpha(66), ft_isalpha(66));
	printf("%d %d\n", isalpha(122), ft_isalpha(122));

	printf("========\n");
	printf("isdigit\n");
	printf("%d %d\n", isdigit(1), ft_isdigit(1));
	printf("%d %d\n", isdigit(45), ft_isdigit(45));
	printf("%d %d\n", isdigit(56), ft_isdigit(56));

	printf("========\n");
	printf("isalnum\n");
	printf("%d %d\n", isalnum(1), ft_isalnum(1));
	printf("%d %d\n", isalnum(45), ft_isalnum(45));
	printf("%d %d\n", isalnum(56), ft_isalnum(56));

	printf("========\n");
	printf("isascii\n");
	printf("%d %d\n", isascii(1), ft_isascii(1));
	printf("%d %d\n", isascii(45), ft_isascii(45));
	printf("%d %d\n", isascii(300), ft_isascii(300));

	printf("========\n");
	printf("isprint\n");
	printf("%d %d\n", isprint(1), ft_isprint(1));
	printf("%d %d\n", isprint(45), ft_isprint(45));
	printf("%d %d\n", isprint(300), ft_isprint(300));

	printf("========\n");
	printf("strlen\n");
	printf("%ld %ld\n", strlen(""), ft_strlen(""));
	printf("%ld %ld\n", strlen("45"), ft_strlen("45"));
	printf("%ld %ld\n", strlen("300"), ft_strlen("300"));
	
	printf("========\n");
	printf("memset\n");
	char *sm = calloc(32, sizeof(char)); ft_print_memory(sm, 32); sm = memset(sm, 'A', 10); print_str(sm);
	printf("========\n");
	sm = calloc(32, sizeof(char)); ft_print_memory(sm, 32); sm = ft_memset(sm, 'A', 10); print_str(sm);

	printf("========\n");
	printf("bzero\n");
	sm = calloc(32, sizeof(char)); sm = ft_memset(sm, 'A', 32); ft_print_memory(sm, 32);    bzero(sm, 5); print_str(sm);
	printf("========\n");
	sm = calloc(32, sizeof(char)); sm = ft_memset(sm, 'A', 32); ft_print_memory(sm, 32); ft_bzero(sm, 5); print_str(sm);

	printf("========\n");
	printf("memcpy\n");
	char *sm4 = calloc(100, sizeof(char)); ft_print_memory(sm4, 32); sm4 = memcpy(sm4, "abcdefghijk", 7); ft_print_memory(sm4, 32); free(sm4);
	char *sm5 = calloc(100, sizeof(char)); ft_print_memory(sm5, 32); sm5 = ft_memcpy(sm5, "abcdefghijk", 7); ft_print_memory(sm5, 32); free(sm5);
	printf("========\n");
	char *sm6 = calloc(100, sizeof(char)); ft_print_memory(sm6, 32); sm6 = memcpy(sm6, "abcdefghijk", 20); ft_print_memory(sm6, 32); free(sm6);
	char *sm7 = calloc(100, sizeof(char)); ft_print_memory(sm7, 32); sm7 = ft_memcpy(sm7, "abcdefghijk", 20); ft_print_memory(sm7, 32); free(sm7);
	//printf("========\n");
	//char sm8[7] = "abcdef"; ft_print_memory(sm8, 32); memcpy(&sm8[2], sm8, 4); ft_print_memory(sm8, 32);
	//printf("========\n");
	//char sm9[7] = "abcdef"; ft_print_memory(sm9, 32); memcpy(sm9, &sm9[2], 4); ft_print_memory(sm9, 32);
	//printf("========\n");
	//char sm10[7] = "abcdef"; ft_print_memory(sm10, 32); ft_memcpy(&sm10[2], sm10, 4); ft_print_memory(sm10, 32);
	//printf("========\n");
	//char sm11[7] = "abcdef"; ft_print_memory(sm11, 32); ft_memcpy(sm11, &sm11[2], 4); ft_print_memory(sm11, 32);

	printf("========\n");
	printf("memmove\n");
	sm = calloc(32, sizeof(char)); ft_memcpy(sm, "abcdef", 7); ft_print_memory(sm, 32); memmove(&sm[2], sm, 4); print_str(sm);
	printf("========\n");
	sm = calloc(32, sizeof(char)); ft_memcpy(sm, "abcdef", 7); ft_print_memory(sm, 32); memmove(sm, &sm[2], 4); print_str(sm);
	printf("========\n");
	sm = calloc(32, sizeof(char)); ft_memcpy(sm, "abcdef", 7); ft_print_memory(sm, 32); ft_memmove(&sm[2], sm, 4); print_str(sm);
	printf("========\n");
	sm = calloc(32, sizeof(char)); ft_memcpy(sm, "abcdef", 7); ft_print_memory(sm, 32); ft_memmove(sm, &sm[2], 4); print_str(sm);

	printf("========\n");
	printf("strlcpy\n");
	char *s100 = malloc(sizeof(char) * 10);
	char *s101 = malloc(sizeof(char) * 10);
	printf("%ld %ld\n", strlcpy(s100, "abcdef", 3), ft_strlcpy(s101, "abcdef", 3));
	printf("%s %s\n", s100, s101);
	free(s100);
	free(s101);

	printf("========\n");
	printf("strlcat\n");
	s100 = malloc(sizeof(char) * 10);
	s101 = malloc(sizeof(char) * 10);
	s100[0] = 0;
	s101[0] = 0;
	printf("%ld %ld\n", strlcat(s100, "abcdef", 3), ft_strlcat(s101, "abcdef", 3));
	printf("%s %s\n", s100, s101);
	free(s100);
	free(s101);

	printf("========\n");
	printf("toupper\n");
	printf("%d %d\n", toupper('a'), ft_toupper('a'));
	printf("%d %d\n", toupper('B'), ft_toupper('B'));

	printf("========\n");
	printf("tolower\n");
	printf("%d %d\n", tolower('a'), ft_tolower('a'));
	printf("%d %d\n", tolower('B'), ft_tolower('B'));

	printf("========\n");
	printf("strchr\n");
	printf("%s %s\n", strchr("abcdefgdhijk", 'd'), ft_strchr("abcdefgdhijk", 'd'));
	printf("%s %s\n", strchr("abcdefgdhijk", 'z'), ft_strchr("abcdefgdhijk", 'z'));

	printf("========\n");
	printf("strrchr\n");
	printf("%s %s\n", strrchr("abcdefgdhijk", 'd'), ft_strrchr("abcdefgdhijk", 'd'));

	printf("========\n");
	printf("strncmp\n");
	printf("%d %d\n", strncmp("abcdefgdhijk", "abcdennn", 5), ft_strncmp("abcdefgdhijk", "abcdennn", 5));
	printf("%d %d\n", strncmp("abcdefgdhijk", "abcdennn", 6), ft_strncmp("abcdefgdhijk", "abcdennn", 6));


	printf("========\n");
	printf("memchr\n");
	printf("%s %s\n", (char *) memchr("abcdefgdhijk", 'd', 10), (char *) ft_memchr("abcdefgdhijk", 'd', 10));
	printf("%s %s\n", (char *) memchr("abcdefgdhijk", 'd', 3), (char *) ft_memchr("abcdefgdhijk", 'd', 3));

	printf("========\n");
	printf("memcmp\n");
	printf("%d %d\n", memcmp("abcdefgdhijk", "abcdennn", 5), ft_memcmp("abcdefgdhijk", "abcdennn", 5));
	printf("%d %d\n", memcmp("abcdefgdhijk", "abcdennn", 6), ft_memcmp("abcdefgdhijk", "abcdennn", 6));

	printf("========\n");
	printf("strnstr\n");
	const char *largestring = "Foo Bar Baz";
	const char *smallstring = "Bar";
	printf("%s %s\n", strnstr(largestring, smallstring, 4), ft_strnstr(largestring, smallstring, 4));
	printf("%s %s\n", strnstr(largestring, smallstring, 10), ft_strnstr(largestring, smallstring, 10));

	printf("========\n");
	printf("atoi\n");
	printf("%d %d\n", atoi("0"), ft_atoi("0"));
	printf("%d %d\n", atoi("1"), ft_atoi("1"));
	printf("%d %d\n", atoi("4213"), ft_atoi("4213"));

	printf("========\n");
	printf("calloc\n");
	char *sc1 = calloc(32, sizeof(char)); print_str(sc1);
	char *sc2 = ft_calloc(32, sizeof(char)); print_str(sc2);

	printf("========\n");
	printf("strdup\n");
	char *s11 =    strdup("abcde"); printf("%s\n", s11); free(s11);
	char *s12 = ft_strdup("abcde"); printf("%s\n", s12); free(s12);
	s11 =    strdup(""); printf("%s\n", s11); free(s11);
	s12 = ft_strdup(""); printf("%s\n", s12); free(s12);

	printf("========\n");
	printf("ft_substr\n");
	char	*s21;
	s21 = ft_substr("abcdefghij",  3,  0); printf("%s\n", s21); if(s21) {free(s21);}
	s21 = ft_substr("abcdefghij",  3,  3); printf("%s\n", s21); if(s21) {free(s21);}
	s21 = ft_substr("abcdefghij",  9, 10); printf("%s\n", s21); if(s21) {free(s21);}
	s21 = ft_substr("abcdefghij", 20, 20); printf("%s\n", s21); if(s21) {free(s21);}

	printf("========\n");
	printf("ft_strjoin\n");
	s21 = ft_strjoin("abcdefghij", "4322"); printf("%s\n", s21); if(s21) {free(s21);}
	s21 = ft_strjoin("", "4322"); printf("%s\n", s21); if(s21) {free(s21);}
	s21 = ft_strjoin("abcdefghij", ""); printf("%s\n", s21); if(s21) {free(s21);}
	s21 = ft_strjoin("", ""); printf("%s\n", s21); if(s21) {free(s21);}

	printf("========\n");
	printf("ft_strtrim\n");
	s21 = ft_strtrim("abcdefghij", "abij"); printf("%s\n", s21); if(s21) {free(s21);}
	s21 = ft_strtrim("abcdefghij", ""); printf("%s\n", s21); if(s21) {free(s21);}
	s21 = ft_strtrim("abcdefghij", "def"); printf("%s\n", s21); if(s21) {free(s21);}
	s21 = ft_strtrim("abcdefghij", "abcdefghij"); printf("%s\n", s21); if(s21) {free(s21);}
	//printf("%s\n", ft_strtrim("abcdefghij", "def"));
	//printf("%s\n", ft_strtrim("abcdefghij", ""));
	//printf("%s\n", ft_strtrim("", "def"));

	printf("========\n");
	printf("ft_split\n");
	int i;
	char **out;
	char **ss;
	out = ft_split("             ","     ");
	ss = out; printf("tab start\n"); i=0;while (*out){ printf("tab[%d]: %s\n",i++,  *out); out++; } printf("tab end\n"); ft_free_strs(ss);
	out = ft_split("                 ","     ");
	ss = out; printf("tab start\n"); i=0;while (*out){ printf("tab[%d]: %s\n",i++,  *out); out++; } printf("tab end\n"); ft_free_strs(ss);
	out = ft_split("yAqQ3CZ","yAqQ3CZ");
	ss = out; printf("tab start\n"); i=0;while (*out){ printf("tab[%d]: %s\n",i++,  *out); out++; } printf("tab end\n"); ft_free_strs(ss);
	out = ft_split("wkiMU","wkiMU");
	ss = out; printf("tab start\n"); i=0;while (*out){ printf("tab[%d]: %s\n",i++,  *out); out++; } printf("tab end\n"); ft_free_strs(ss);
	out = ft_split("hX7znA5kIZJmGk0qvEmi7nnWEvC uVWMMAnWhncuu","MApm");
	ss = out; printf("tab start\n"); i=0;while (*out){ printf("tab[%d]: %s\n",i++,  *out); out++; } printf("tab end\n"); ft_free_strs(ss);
	out = ft_split("j EWYPJrAYn84QcxPCvfE1zSGavBfWa","SbPRYtf");
	ss = out; printf("tab start\n"); i=0;while (*out){ printf("tab[%d]: %s\n",i++,  *out); out++; } printf("tab end\n"); ft_free_strs(ss);
	out = ft_split("hn8UnRhrCUwQGrQoS1Y0    PIuYTEpr","5Z2w");
	ss = out; printf("tab start\n"); i=0;while (*out){ printf("tab[%d]: %s\n",i++,  *out); out++; } printf("tab end\n"); ft_free_strs(ss);
	out = ft_split("UsXMRa1JtpU7ig7MhMcYoSkkPZFrGlWyp8clSMm02wJAdsj","DJ");
	ss = out; printf("tab start\n"); i=0;while (*out){ printf("tab[%d]: %s\n",i++,  *out); out++; } printf("tab end\n"); ft_free_strs(ss);
	out = ft_split("sjGpjG0iuz14BUzWYqoNdwtJJNGqwkQdEH    rCNjoEr","MO");
	ss = out; printf("tab start\n"); i=0;while (*out){ printf("tab[%d]: %s\n",i++,  *out); out++; } printf("tab end\n"); ft_free_strs(ss);
	out = ft_split("OpzRLhpjFlyoTDdiKK UMsFAvLNTx2YAVRnDSoOdzUgMkJ9","LnCx");
	ss = out; printf("tab start\n"); i=0;while (*out){ printf("tab[%d]: %s\n",i++,  *out); out++; } printf("tab end\n"); ft_free_strs(ss);
	out = ft_split("  gh  "," gh");
	ss = out; printf("tab start\n"); i=0;while (*out){ printf("tab[%d]: %s\n",i++,  *out); out++; } printf("tab end\n"); ft_free_strs(ss);
	out = ft_split("  gh  "," ");
	ss = out; printf("tab start\n"); i=0;while (*out){ printf("tab[%d]: %s\n",i++,  *out); out++; } printf("tab end\n"); ft_free_strs(ss);
	out = ft_split("owaaNTKwCcN8Cb    Hfg3a P5Di1cabSFVflXMihAfBc0C","");
	ss = out; printf("tab start\n"); i=0;while (*out){ printf("tab[%d]: %s\n",i++,  *out); out++; } printf("tab end\n"); ft_free_strs(ss);

	
	printf("========\n");
	printf("ft_itoa\n");
	char *s29;
	s29 = ft_itoa(0); printf("%d %s\n", 0, s29); if (s29) {free(s29);}
	s29 = ft_itoa(-0); printf("%d %s\n", -0, s29); if (s29) {free(s29);}
	s29 = ft_itoa(100234); printf("%d %s\n", 100234, s29); if (s29) {free(s29);}
	s29 = ft_itoa(INT_MIN); printf("%d %s\n", INT_MIN, s29); if (s29) {free(s29);}
	s29 = ft_itoa(INT_MAX); printf("%d %s\n", INT_MAX, s29); if (s29) {free(s29);}

	printf("========\n");
	printf("ft_striteri\n");
	s29 = ft_strdup("owaaNTKwCcN8Cb"); printf("%s\n", s29); ft_striteri(s29, &test1); printf("%s\n", s29); if (s29) {free(s29);}
	printf("========\n");
	s29 = ft_strdup("owaaNTKwCcN8Cb"); printf("%s\n", s29); ft_striteri(s29, &test2); printf("%s\n", s29); if (s29) {free(s29);}
	
	printf("========\n");
	printf("ft_strmapi\n");
	s29 = ft_strmapi("owaaNTKwCcN8Cb", &test3); printf("%s\n", s29); if (s29) {free(s29);}
	printf("========\n");
	s29 = ft_strmapi("owaaNTKwCcN8Cb", &test4); printf("%s\n", s29); if (s29) {free(s29);}

	printf("========\n");
	printf("ft_putchar_fd\n");
	ft_putchar_fd('c', 1);
	ft_putchar_fd(0, 1);
	ft_putchar_fd(200, 1);
	ft_putchar_fd('\n', 1);

	printf("========\n");
	printf("ft_putstr_fd\n");
	ft_putstr_fd("c", 1);
	ft_putstr_fd("", 1);
	ft_putstr_fd("10 00", 1);
	ft_putstr_fd("\n", 1);

	printf("========\n");
	printf("ft_putendl_fd\n");
	ft_putendl_fd("c", 1);
	ft_putendl_fd("", 1);
	ft_putendl_fd("10 00", 1);

	printf("========\n");
	printf("ft_putnbr_fd\n");
	ft_putnbr_fd(0, 1); ft_putchar_fd('\n', 1);
	ft_putnbr_fd(-0, 1); ft_putchar_fd('\n', 1);
	ft_putnbr_fd(100234, 1); ft_putchar_fd('\n', 1);
	ft_putnbr_fd(INT_MIN, 1); ft_putchar_fd('\n', 1);
	ft_putnbr_fd(INT_MAX, 1); ft_putchar_fd('\n', 1);

	printf("========\n");
	printf("ft_lstadd_front, ft_lstaddback, ft_lstclear\n");
	t_list	**new, **new1;
	new = malloc(sizeof(t_list *));
	new[0] = 0;
	ft_lstadd_front(new, ft_lstnew(ft_strdup("sdfhFJhS")));
	ft_lstadd_front(new, ft_lstnew(ft_strdup("")));
	ft_lstadd_back(new, ft_lstnew(ft_strdup("asidjdsfOIHI")));
	ft_lstadd_back(new, ft_lstnew(ft_strdup("")));
	ft_list_print(new[0]);
	ft_lstclear(new, &free);

	printf("========\n");
	char **out1 = ft_split("OpzRLhpjFlyoTDdiKK UMsFAvLNTx2YAVRnDSoOdzUgMkJ9","LnCx");
	new = malloc(sizeof(t_list *));
	new[0] = ft_list_push_strs(out1);
	ft_list_print(new[0]);
	ft_lstadd_front(new, ft_lstnew(ft_strdup("sdfhFJhS")));
	ft_lstadd_front(new, ft_lstnew(ft_strdup("")));
	ft_lstadd_back(new, ft_lstnew(ft_strdup("asidjdsfOIHI")));
	ft_lstadd_back(new, ft_lstnew(ft_strdup("")));
	ft_list_print(new[0]);
	ft_lstclear(new, &free);
	free(out1);

	printf("========\n");
	printf("ft_lstiter\n");
	out1 = ft_split("OpzRLhpjFlyoTDdiKK UMsFAvLNTx2YAVRnDSoOdzUgMkJ9","LnCx");
	new = malloc(sizeof(t_list *));
	new[0] = ft_list_push_strs(out1);
	ft_list_print(new[0]);
	ft_lstiter(new[0], test5);
	ft_list_print(new[0]);
	ft_lstclear(new, &free);
	free(out1);

	printf("========\n");
	out1 = ft_split("OpzRLhpjFlyoTDdiKK UMsFAvLNTx2YAVRnDSoOdzUgMkJ9","LnCx");
	new = malloc(sizeof(t_list *));
	new[0] = ft_list_push_strs(out1);
	ft_list_print(new[0]);
	ft_lstiter(new[0], test6);
	ft_list_print(new[0]);
	ft_lstclear(new, &free);
	free(out1);

	printf("========\n");
	printf("ft_lstmap\n");
	out1 = ft_split("OpzRLhpjFlyoTDdiKK UMsFAvLNTx2YAVRnDSoOdzUgMkJ9","LnCx");
	new = malloc(sizeof(t_list *));
	new1 = malloc(sizeof(t_list *));
	new[0] = ft_list_push_strs(out1);
	ft_list_print(new[0]);
	new1[0] = ft_lstmap(new[0], test7, free);
	ft_list_print(new1[0]);
	ft_lstclear(new, &free);
	ft_lstclear(new1, &free);
	free(out1);

	printf("========\n");
	out1 = ft_split("OpzRLhpjFlyoTDdiKK UMsFAvLNTx2YAVRnDSoOdzUgMkJ9","LnCx");
	new = malloc(sizeof(t_list *));
	new1 = malloc(sizeof(t_list *));
	new[0] = ft_list_push_strs(out1);
	ft_list_print(new[0]);
	new1[0] = ft_lstmap(new[0], test8, free);
	ft_list_print(new1[0]);
	ft_lstclear(new, &free);
	ft_lstclear(new1, &free);
	free(out1);

}
