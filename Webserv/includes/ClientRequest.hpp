/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientRequest.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/16 16:11:46 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#ifndef CLIENTREQUEST_HPP
# define CLIENTREQUEST_HPP

class ClientRequest
{
	private:
		int		_socket;
		std::string	_http_request;
		std::string	_header;
		std::string	_body;
		std::string	_method;
		std::string	_url;

		ClientRequest();
		ClientRequest(const ClientRequest&);
		ClientRequest &operator=(const ClientRequest& op);
	public:
		ClientRequest(int);
		virtual ~ClientRequest();

		void		clean(void);
		void		set_method(std::string);
		void		set_http_request(std::string);
		void		cat_http_request(std::string);

		std::string	get_method(void) const;
		std::string	get_http_request(void) const;
};

#endif
