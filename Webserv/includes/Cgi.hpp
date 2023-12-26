/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/12/26 10:00:07 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#ifndef CGI_HPP
# define CGI_HPP
/* 
class	Server;
class	Location;
class	Request;
class	Configuration;
*/
class	Cgi
{
	private:
        std::string     _pass;
        std::string     _file;
		Request*	    _request;
		//Response*	_response;

		Cgi();
		Cgi(const Cgi&);
		Cgi	&operator=(const Cgi& op);
	public:
		Cgi(std::string, std::string, Response*);
		virtual ~Cgi();
};

#endif
