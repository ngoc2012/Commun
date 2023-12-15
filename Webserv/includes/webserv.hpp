/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 22:38:19 by ngoc              #+#    #+#             */
/*   Updated: 2023/12/15 09:02:15 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>
#include <sys/stat.h>	// stat, S_ISDIR
#include <sys/select.h>	// select

#include <iostream>
#include <vector>
#include <map>
#include <fstream>

#ifndef WEBSERV_HPP
# define WEBSERV_HPP

# define NPOS std::string::npos

enum	e_method {GET, POST, PUT, NONE};

std::vector<std::string>	split_string(const std::string& input, std::string delimiters);
bool				is_digit(std::string& str);
std::string			itos(int n);
bool                match_wildcard(const char* str, const char* pattern);

#endif
