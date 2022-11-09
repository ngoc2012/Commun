#include <stdio.h>
#include "Libft/libft.h"
#include "Libs/libft.h"
#include <ctype.h>
#include <string.h>
#include <bsd/string.h>
#include <stdlib.h>

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
	char *sm = malloc(sizeof(char) * 10); ft_print_memory(sm, 32); sm = memset(sm, 'A', 10); ft_print_memory(sm, 32);
	printf("========\n");
	char *sm1 = malloc(sizeof(char) * 10); ft_print_memory(sm1, 32); sm1 = ft_memset(sm1, 'A', 10); ft_print_memory(sm1, 32);
	printf("========\n");
	char *sm2 = malloc(sizeof(char) * 10); ft_print_memory(sm2, 32); sm2 = memset(sm2, 'A', 20); ft_print_memory(sm2, 32); free(sm2);
	printf("========\n");
	char *sm3 = malloc(sizeof(char) * 10); ft_print_memory(sm3, 32); sm3 = ft_memset(sm3, 'A', 20); ft_print_memory(sm3, 32); free(sm3);

	printf("========\n");
	printf("bzero\n");
	ft_print_memory(sm, 32); bzero(sm, 5); ft_print_memory(sm, 32); free(sm);
	printf("========\n");
	ft_print_memory(sm1, 32); ft_bzero(sm1, 5); ft_print_memory(sm1, 32); free(sm1);

	printf("========\n");
	printf("memcpy\n");
	char *sm4 = malloc(sizeof(char) * 100); ft_print_memory(sm4, 32); sm4 = memcpy(sm4, "abcdefghijk", 7); ft_print_memory(sm4, 32); free(sm4);
	printf("========\n");
	char *sm5 = malloc(sizeof(char) * 100); ft_print_memory(sm5, 32); sm5 = memcpy(sm5, "abcdefghijk", 7); ft_print_memory(sm5, 32); free(sm5);
	printf("========\n");
	char *sm6 = malloc(sizeof(char) * 100); ft_print_memory(sm6, 32); sm6 = memcpy(sm6, "abcdefghijk", 20); ft_print_memory(sm6, 32); free(sm6);
	printf("========\n");
	char *sm7 = malloc(sizeof(char) * 100); ft_print_memory(sm7, 32); sm7 = memcpy(sm7, "abcdefghijk", 20); ft_print_memory(sm7, 32); free(sm7);
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
	char sm12[7] = "abcdef"; ft_print_memory(sm12, 32); memmove(&sm12[2], sm12, 4); ft_print_memory(sm12, 32);
	printf("========\n");
	char sm13[7] = "abcdef"; ft_print_memory(sm13, 32); memmove(sm13, &sm13[2], 4); ft_print_memory(sm13, 32);
	printf("========\n");
	char sm14[7] = "abcdef"; ft_print_memory(sm14, 32); ft_memmove(&sm14[2], sm14, 4); ft_print_memory(sm14, 32);
	printf("========\n");
	char sm15[7] = "abcdef"; ft_print_memory(sm15, 32); ft_memmove(sm15, &sm15[2], 4); ft_print_memory(sm15, 32);

	char *s = malloc(sizeof(char) * 10);
	printf("========\n");
	printf("strlcpy\n");
	printf("%ld %ld\n", strlcpy(s, "1234", 3), ft_strlcpy(s, "1234", 3));
	strlcpy(s, "1234", 3);printf("%s ", s);
	ft_strlcpy(s, "1234", 3);printf("%s\n", s);

	printf("========\n");
	printf("strlcat\n");
	s[0] = 0;
	printf("%ld %ld\n", strlcat(s, "1234", 3), ft_strlcat(s, "1234", 3));
	printf("s = %s\n", s);
	strlcat(s, "1234", 5);printf("%s ", s);
	ft_strlcat(s, "1234", 7);printf("%s\n", s);

	free(s);

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

	//printf("========\n");
	//printf("memchr\n");
	//printf("%s %s\n", (char *) memchr("abcdefgdhijk", 'd', 10), (char *) ft_memchr("abcdefgdhijk", 'd', 10));
	//printf("%s %s\n", (char *) memchr("abcdefgdhijk", 'd', 3), (char *) ft_memchr("abcdefgdhijk", 'd', 3));

	//printf("========\n");
	//printf("memcmp\n");
	//printf("%d %d\n", memcmp("abcdefgdhijk", "abcdennn", 5), ft_memcmp("abcdefgdhijk", "abcdennn", 5));
	//printf("%d %d\n", memcmp("abcdefgdhijk", "abcdennn", 6), ft_memcmp("abcdefgdhijk", "abcdennn", 6));

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
	//printf("%d\n", sizeof(char));
	//char	*s1 = calloc(10, sizeof(char));
	//char	*s2 = ft_calloc(10, sizeof(char));
	//for (int i = 0; i < 10; i++)
	//	printf("%d", s1[i]);
	//printf(" ");
	//for (int i = 0; i < 10; i++)
	//	printf("%d", s2[i]);
	//printf("\n");
	//free(s1);
	//free(s2);

	//printf("========\n");
	//printf("strdup\n");
	//char	*s11 = strdup("abcde");
	//char	*s12 = ft_strdup("abcde");
	//printf("%s %s\n", s11, s12);
	//free(s11);
	//free(s12);

	//printf("========\n");
	//printf("ft_substr\n");
	//char	*s21 = ft_substr("abcdefghij", 3, 3); printf("%s\n", s21); free(s21);
	//char	*s22 = ft_substr("abcdefghij", 10, 10); printf("%s\n", s22); free(s22);
	//printf("%s\n", ft_substr("abcdefghij", 10, 10));
	//printf("%s\n", ft_substr("abcdefghij", 20, 20));

	//printf("========\n");
	//printf("ft_strjoin\n");
	//printf("%s\n", ft_strjoin("abcdefghij", "4322"));
	//printf("%s\n", ft_strjoin("", "4322"));
	//printf("%s\n", ft_strjoin("abcdefghij", ""));

	//printf("========\n");
	//printf("ft_strtrim\n");
	//printf("%s\n", ft_strtrim("abcdefghij", "def"));
	//printf("%s\n", ft_strtrim("abcdefghij", ""));
	//printf("%s\n", ft_strtrim("", "def"));

	//printf("========\n");
	//printf("ft_split\n");
	//char **out;
	//char **ss;
	//out = ft_split("             ","     ");
	//ss = out; printf("tab start\\n"); i=0;while (*out){ printf("tab[%d]: %s\\n",i++,  *out); out++; } printf("tab end\\n"); free(ss);
	//out = ft_split("                 ","     ");
	//ss = out; printf("tab start\\n"); i=0;while (*out){ printf("tab[%d]: %s\\n",i++,  *out); out++; } printf("tab end\\n"); free(ss);
	//out = ft_split("yAqQ3CZ","yAqQ3CZ");
	//ss = out; printf("tab start\\n"); i=0;while (*out){ printf("tab[%d]: %s\\n",i++,  *out); out++; } printf("tab end\\n"); free(ss);
	//out = ft_split("wkiMU","wkiMU");
	//ss = out; printf("tab start\\n"); i=0;while (*out){ printf("tab[%d]: %s\\n",i++,  *out); out++; } printf("tab end\\n"); free(ss);
	//out = ft_split("hX7znA5kIZJmGk0qvEmi7nnWEvC uVWMMAnWhncuu","MApm");
	//ss = out; printf("tab start\\n"); i=0;while (*out){ printf("tab[%d]: %s\\n",i++,  *out); out++; } printf("tab end\\n"); free(ss);
	//out = ft_split("j EWYPJrAYn84QcxPCvfE1zSGavBfWa","SbPRYtf");
	//ss = out; printf("tab start\\n"); i=0;while (*out){ printf("tab[%d]: %s\\n",i++,  *out); out++; } printf("tab end\\n"); free(ss);
	//out = ft_split("hn8UnRhrCUwQGrQoS1Y0    PIuYTEpr","5Z2w");
	//ss = out; printf("tab start\\n"); i=0;while (*out){ printf("tab[%d]: %s\\n",i++,  *out); out++; } printf("tab end\\n"); free(ss);
	//out = ft_split("UsXMRa1JtpU7ig7MhMcYoSkkPZFrGlWyp8clSMm02wJAdsj","DJ");
	//ss = out; printf("tab start\\n"); i=0;while (*out){ printf("tab[%d]: %s\\n",i++,  *out); out++; } printf("tab end\\n"); free(ss);
	//out = ft_split("sjGpjG0iuz14BUzWYqoNdwtJJNGqwkQdEH    rCNjoEr","MO");
	//ss = out; printf("tab start\\n"); i=0;while (*out){ printf("tab[%d]: %s\\n",i++,  *out); out++; } printf("tab end\\n"); free(ss);
	//out = ft_split("OpzRLhpjFlyoTDdiKK UMsFAvLNTx2YAVRnDSoOdzUgMkJ9","LnCx");
	//ss = out; printf("tab start\\n"); i=0;while (*out){ printf("tab[%d]: %s\\n",i++,  *out); out++; } printf("tab end\\n"); free(ss);
	//out = ft_split("  gh  "," gh");
	//ss = out; printf("tab start\\n"); i=0;while (*out){ printf("tab[%d]: %s\\n",i++,  *out); out++; } printf("tab end\\n"); free(ss);
	//out = ft_split("  gh  "," ");
	//ss = out; printf("tab start\\n"); i=0;while (*out){ printf("tab[%d]: %s\\n",i++,  *out); out++; } printf("tab end\\n"); free(ss);
	//out = ft_split("owaaNTKwCcN8Cb    Hfg3a P5Di1cabSFVflXMihAfBc0C","");
	//ss = out; printf("tab start\\n"); i=0;while (*out){ printf("tab[%d]: %s\\n",i++,  *out); out++; } printf("tab end\\n"); free(ss);

}
