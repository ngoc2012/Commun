/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Configuration.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/10 09:12:38 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Configuration.hpp"

Configuration::Configuration()
{
	clean();
}
Configuration::Configuration(const Configuration& src) { *this = src; }
Configuration&	Configuration::operator=( Configuration const & src )
{
	(void) src;
	return (*this);
}
Configuration::~Configuration() {}
void	Configuration::clean()
{
	_http_request = "";
	_method = "";
	_url = "";
}
std::string	Configuration::get_http_request(void) {return (_http_request);}
void	Configuration::set_http_request(std::string s) {_http_request = s;}
