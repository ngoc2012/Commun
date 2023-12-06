/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/12/06 15:02:38 by ngoc             ###   ########.fr       */
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

		Response(const Response&);
		Response	&operator=(const Response& op);
	public:
		//Response(int, Host*, Server*, Request*);
		Response();
		virtual ~Response();

		void		send(void);
		size_t		get_content_length(void) const;
		Location*	get_location(void) const;	

		void		set_socket(int);
		void		set_host(Host*);
		void		set_server(Server*);
		void		set_request(Request*);
		void		set_status_code(int);
};

#endif
