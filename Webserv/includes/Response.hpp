/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/25 19:14:00 by ngoc             ###   ########.fr       */
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
		int		_socket;
		Host*		_host;
		Server*		_server;
		ClientRequest*	_request;
		Location*	_location;	
		size_t		_content_length;
		int		_status_code;
		std::string	_full_file_name;
		std::string	_body;

		bool		find_method(e_method, std::vector<e_method>);
		bool		compare_url(std::string, std::string);
		void		find_location(std::string);
		std::string	get_methods_str(void);
		std::string	get_file_extension(std::string&);
		void		get_full_file_name(std::string);
		std::string	get(void);

		Response();
		Response(const Response&);
		Response		&operator=(const Response& op);
	public:
		Response(int, Host*, Server*, ClientRequest*);
		virtual ~Response();

		void		send(void);
		size_t		get_content_length(void) const;
		Location*	get_location(void) const;	
};

#endif
