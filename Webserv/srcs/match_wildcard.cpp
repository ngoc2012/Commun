/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_wildcard.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 11:06:57 by ngoc              #+#    #+#             */
/*   Updated: 2023/12/06 11:11:17 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

bool    match_wildcard(const char* str, const char* pattern) {
    while (*pattern) {
        if (*pattern == '*') {
            pattern++;
            if (!*pattern) { return (true); }
            while (*str && *str != *pattern) { str++; }
        } else {
            if (*str != *pattern) { return (false); }
            str++;
            pattern++;
        }
    }
    return (*str == 0);
}
