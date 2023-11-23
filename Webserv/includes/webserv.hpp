/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 22:38:19 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/23 11:29:48 by ngoc             ###   ########.fr       */
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

enum	e_method {GET, POST, PUT, NONE};

std::vector<std::string>	split_string(const std::string& input, std::string delimiters);
bool				is_digit(std::string& str);

#endif
