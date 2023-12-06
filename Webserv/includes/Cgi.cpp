/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/12/06 15:05:55 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#ifndef CGI_HPP
# define CGI_HPP
 
class	Server;
class	Location;
class	Request;
class	Configuration;

class	Cgi
{
	private:
		Response*	_response;

		Cgi(const Cgi&);
		Cgi	&operator=(const Cgi& op);
	public:
		Cgi();
		virtual ~Cgi();
};

#endif
