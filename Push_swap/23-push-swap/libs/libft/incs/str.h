/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wetieven <wetieven@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 14:19:30 by wetieven          #+#    #+#             */
/*   Updated: 2022/02/18 12:28:57 by wetieven         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef STR_H
# define STR_H

# include "err.h"

/*
** String check
*/
size_t	ft_strlen(const char *src);
int		ft_word_count(const char *str, const char sep);
int		ft_strncmp(const char *src, const char *cmp, size_t len);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strchr(const char *str, int c);
char	*ft_strrchr(const char *src, int c);
char	*ft_strnstr(const char *hstk, const char *ndle, size_t len);
t_error	file_ext_chk(const char *file_name, const char *extension);
int		ft_isnumbr(char *str);

/*
** String manipulation
*/
char	*ft_strcpy(char *dst, const char *src);
size_t	ft_strlcpy(char *dst, const char *src, size_t dst_size);
size_t	ft_strlcat(char *stem, const char *appn, size_t dst_size);

/*
** String creation
*/
char	*ft_strdup(const char *src);
char	*ft_strjoin(char const *pre, char const *post);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

/*
** String parsing
*/
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strtrim(char const *str, char const *charset);
char	**ft_split(char const *str, char sep);

#endif
