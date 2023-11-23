/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/23 10:23:40 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#ifndef RESPONSE_HPP
# define RESPONSE_HPP
 
class	ClientRequest
{
	private:
		int		_socket;
		Host*		_host;
		int		_error;
		std::string	_header;
		std::string	_body;
		std::string	_content_type0;
		std::string	_content_type1;
		std::string	_url;
		e_method	_method;

		ClientRequest();
		ClientRequest(const ClientRequest&);
		ClientRequest &operator=(const ClientRequest& op);
	public:
		ClientRequest(int, Host*);
		virtual ~ClientRequest();

		int		read_client_request(void);
		bool		read_header(void);
		int		read_error(std::string, int);
		void		clean(void);
		bool		parser_header(void);
		bool		read_method(std::string&);
		bool		read_content_type(std::string&, std::string&);
		bool		read_body(void);
		bool		find_start_body(std::string&);
};

#endif
