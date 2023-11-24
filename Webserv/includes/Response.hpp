/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/24 17:24:15 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#ifndef RESPONSE_HPP
# define RESPONSE_HPP
 
class	Server;
class	Location;
class	ClientRequest;
class	ConfigurationParser;

class	Response
{
	private:
		int			_socket;
		Host*			_host;
		Server*			_server;
		ClientRequest*		_request;
		std::vector<Location*>	_locations;	

		std::vector<e_method>::iterator		find_method(e_method m, std::vector<e_method> methods);
		bool					find_url(std::string url, std::string l_url);
		std::vector<Location*>::iterator	find_location(std::string url);

		Response();
		Response(const Response&);
		Response		&operator=(const Response& op);
	public:
		Response(int, Host*, Server*, ClientRequest*);
		virtual ~Response();

		void		send(void);
		size_t		get_content_length(void) const;
};

#endif
