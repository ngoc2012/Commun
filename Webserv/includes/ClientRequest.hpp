/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientRequest.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/17 22:20:47 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#ifndef CLIENTREQUEST_HPP
# define CLIENTREQUEST_HPP
 
enum	e_method {GET, POST, NONE};

class	Host;

class	ClientRequest
{
	private:
		int		_socket;
		Host*		_host;
		int		_error;
		std::string	_http_request;
		std::string	_header;
		std::string	_body;
		e_method	_method;
		std::string	_content_type0;
		std::string	_content_type1;
		std::string	_url;

		ClientRequest();
		ClientRequest(const ClientRequest&);
		ClientRequest &operator=(const ClientRequest& op);
	public:
		ClientRequest(int, Host*);
		virtual ~ClientRequest();

		void		cat_http_request(std::string);
		void		read_client_request(void);
		void		clean(void);
		bool		read_header(std::string&);
		bool		read_method(std::string&);
		bool		read_content_type(std::string&);

		//std::string	get_method(void) const;
		std::string	get_http_request(void) const;

		//void		set_method(std::string);
		void		set_http_request(std::string);
};

#endif
