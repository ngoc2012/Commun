/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 22:38:19 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/21 08:17:30 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
# define WEBSERV_HPP

enum	e_method {GET, POST, PUT, NONE};

std::vector<std::string>	split_string(const std::string& input, std::string delimiters);
bool				is_digit(std::string& str);

#endif
