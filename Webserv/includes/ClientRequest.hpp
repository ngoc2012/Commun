/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientRequest.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/23 22:23:37 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#ifndef CLIENTREQUEST_HPP
# define CLIENTREQUEST_HPP
 
# define BUFFER	2048

class	Host;

class	ClientRequest
{
	private:
		int		_socket;
		Host*		_host;
		Server*		_server;

		int		_error;
		std::string	_header;
		std::string	_body;
		std::string	_content_type0;
		std::string	_content_type1;
		std::string	_url;
		e_method	_method;

		bool		read_header(void);
		int		read_error(std::string, int);
		void		clean(void);
		bool		parser_header(void);
		bool		read_method(std::string&);
		bool		read_content_type(std::string&, std::string&);
		bool		read_body(void);
		bool		find_start_body(std::string&);

		ClientRequest();
		ClientRequest(const ClientRequest&);
		ClientRequest &operator=(const ClientRequest& op);
	public:
		ClientRequest(int, Host*, Server*);
		virtual ~ClientRequest();

		int		read_client_request(void);
};

#endif
