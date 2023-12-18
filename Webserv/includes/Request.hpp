/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/12/18 13:58:10 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include "Response.hpp"

#ifndef CLIENTREQUEST_HPP
# define CLIENTREQUEST_HPP
 
# define HEADER_BUFFER 1024

class	Host;

class	Request
{
	private:
		int		    _socket;
		Host*		_host;
		Server*		_server;
		Response	_response;

		int		    _status_code;
		std::string	_header;
		std::string	_body_in_header;
		size_t		_body_size;
        char		_raw[HEADER_BUFFER + 1];
		std::string	_content_type;
		std::string	_url;
		e_method	_method;

		void		read_header(void);
		void		clean(void);
		bool		parser_header(void);
		bool		read_method(std::string&);
		bool		read_content_type(std::string&, std::string&);
		bool		split_header_body(std::string&);

		Request();
		Request(const Request&);
		Request &operator=(const Request& op);
	public:
		Request(int, Host*, Server*);
		virtual ~Request();

		void		read();
		e_method	get_method(void) const;
		std::string	get_url(void) const;
		Response*	get_response(void);
		int		    get_status_code(void) const;
        std::string	get_body_in_header(void) const;
        std::string	get_content_type(void) const;
        size_t		get_body_size(void) const;
        std::string	get_header(void) const;
};

#endif
